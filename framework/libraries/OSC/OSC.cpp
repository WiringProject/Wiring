/* $Id: OSC.cpp 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Bjoern Hartmann <bjoern@cs.stanford.edu>
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | OSC Library.
|| | http://wiring.org.co/learning/topics/wiringosc.html
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
|| @TODO
|| | CLEANUP AND MINIMIZING RAM FOOTPRINT
|| #
*/

#include "OSC.h"

WOSC OSC(Serial);

const char WOSC::prefixReport[9] = "/report/";
const char WOSC::prefixPinmode[11] = "/pinmode/";
const char WOSC::prefixOut[6] = "/out/";
const char WOSC::prefixPwm[6] = "/pwm/";
const char WOSC::prefixIn[5] ="/in/";
const char WOSC::prefixA2d[6] ="/adc/";
const char WOSC::prefixReset[7] ="/reset"; //TODO: implement
//const byte WOSC::pwmPinMap[6] = {37, 36, 35, 31, 30, 29};

/*
|| @constructor
|| | Initialize the OCS object
|| #
|| 
|| @parameter s The Stream to read and write WOSC messages from and to
*/
WOSC::WOSC(Stream &s) : stream(&s) 
{
  oscRxNextOp = OSC_RXOP_WAITFORSTART;
  k = FIRST_ANALOG_PIN;
  int i;
  
  reportAnalog=0x00;
  reportDigital=true;
  
  // set all pins as inputs   
  for(i=FIRST_DIGITAL_PIN; i<=LAST_DIGITAL_PIN; i++) 
  {
    if((i!=RX_PIN) && (i != TX_PIN)) 
    {
      pinMode(i,INPUT);
      digitalWrite(i,HIGH); // use pull-ups
    }
  }
}

/*
|| @description
|| | Initialize the serial stream
|| #
*/
void WOSC::begin() 
{
  //@TODO this is not good design because we might want to use another serial port
  //THIS IS IMPORTANT
  Serial.begin(OSC_SERIAL_SPEED);
}

/*
|| @description
|| | Handle I/O 
|| | Parse the received chars at the stream 
|| #
*/
void WOSC::transmit() 
{
  // check all digital inputs
  if(reportDigital) 
  {
    checkDiscreteInputs();
  }

  // check one analog input per loop
  if(reportAnalog & (1<<k))
  {
    checkAnalogInput(k);
  }
  k=(k+1)%NUM_ANALOG_PINS;
  
  // handle all received serial bytes
  while (stream->available() > 0) 
  {
    int incomingByte = stream->read() & 0xFF;// read byte - truncate to 8bits to be safe
    parse(incomingByte); // hand to message parser
  }
}

/*
|| @description
|| | Send a message over OSC
|| |
|| | @parameter address  the target address to send the value to
|| | @parameter value    the payload to deliver to the address
|| #
*/
void WOSC::sendMessage(char *address, unsigned long value)
{
  sendMessageInt(address,value);
}

/// private methods

void WOSC::sendMessageInt(char * address, unsigned long value)
{
  byte offset=0;
  byte i=0;

  // clear buffer
  for(i=0; i<MAX_LENGTH; i++) 
  {
    oscBuffer[i]=0x00;
  }

  //write packet header
  oscBuffer[offset++]=0xBE;

  //compute message length 
  //first compute address string length and padd if necessary
  byte addrlen = strlen(address);
  if(addrlen&0x03)				
    addrlen += 4-(addrlen&0x03);

  //then add type-tag length and arg length (both 4 for a simple int message)
  byte typetaglen=4;
  byte arglen = 4;

  //final length is sum of the three
  byte len = addrlen+typetaglen+arglen;

  //write message length
  oscBuffer[offset++]=(unsigned char)len;

  //write address
  strcpy(oscBuffer+offset,address); 
  offset+=addrlen;

  //write typetag
  oscBuffer[offset++]=',';
  oscBuffer[offset++]='i';
  oscBuffer[offset++]=0x00;
  oscBuffer[offset++]=0x00;

  //write argument
  oscBuffer[offset++]=*(((unsigned char *)(&value))+3);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+2);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+1);
  oscBuffer[offset++]=*(((unsigned char *)(&value))+0);

  //compute + write checksum
  byte checksum=0;
  for(i=2; i<offset; i++) 
  {
    checksum+=oscBuffer[i];
  }
  oscBuffer[offset++]=checksum;

  //send message byte-by-byte
  for(i=0;i<offset;i++) 
  {
    stream->print(oscBuffer[i],BYTE);
  }
}

void WOSC::receiveMessageInt(char * msg, unsigned long value)
{
  int i;
  int outPin;
  
  //uncomment to echo message back for debugging
  //sendMessageInt(msg,value);
  
  // check if this is an output message, i.e., starts with "/out/"
  if(strncmp(msg,prefixOut,strlen(prefixOut))==0) 
  {
    //if so, find which pin
    outPin = atoi(msg+strlen(prefixOut));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN && outPin!=RX_PIN && outPin!=TX_PIN) //sanity check
    { 
      //change its value
      //note: pin can be set to input - this enables/disables pullups
      digitalWrite(outPin,(byte)(value & 0x01)); 
    }
    return;
  }

  // check if this is a pwm message, i.e., starts with "/pwm/"
  if(strncmp(msg,prefixPwm,strlen(prefixPwm))==0) 
  {
    outPin = atoi(msg+strlen(prefixPwm));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN  && outPin!=RX_PIN && outPin!=TX_PIN) //sanity check
    { 
      //make sure we turn pin into output in our pinDir first
      //so we don't generate lots of extraneous messages
      
      //may need to map from 0..5 to 29..37 range as well
// BH: Changed requirements - you *MUST* specify the absolute PWM pin number
//      if(0<=outPin && 5 >= outPin)
//      {
//        pinDir[pwmPinMap[outPin]/8] = pinDir[pwmPinMap[outPin]/8] |  (1<<(pwmPinMap[outPin]%8));
//      } 
//      else 
//      {
        pinDir[outPin/8] = pinDir[outPin/8] | (1<<(outPin%8));
//      }
      
      //set pwm
      analogWrite(outPin,value&1023);
    }
    return;
  }

  // check if this is a "report" message which starts with "/report/"
  // changes which pins get reported
  if(strncmp(msg,prefixReport,strlen(prefixReport))==0) 
  {
    //if it continues with "/in"

    if(strncmp(msg+strlen(prefixReport)-1,prefixIn,strlen(prefixIn)-1)==0)
    {
      reportDigital = (value!=0);
      return;
    }
    //else if it continues with "/adc/"
    else if(strncmp(msg+strlen(prefixReport)-1,prefixA2d,strlen(prefixA2d))==0) 
    {
      //extract which analog pin we're talking about
      outPin = atoi(msg+strlen(prefixReport)-1+strlen(prefixA2d));
      //flip the bit in reportAnalog:
      if(outPin>=FIRST_ANALOG_PIN && outPin<=LAST_ANALOG_PIN) //sanity check
      { 
        if(value==0) 
        {
          reportAnalog = reportAnalog & ~(1<<outPin);
        }   
        else 
        {
          reportAnalog = reportAnalog | (1<<outPin);
        }
      }
      return;
    }
    //else if it continues with "/adc" (no final slash)
    else if(strncmp(msg+strlen(prefixReport)-1,prefixA2d,strlen(prefixA2d)-1)==0) 
    {
      //turn reporting for all analog pins on or off
      if(value==0) 
      {
        reportAnalog=0x00;
      } 
      else 
      {
        reportAnalog=0xFF;
      }
      return;
    }
    
  }
  
  //finally, this could be a "/pinmode/ message"
  if(strncmp(msg,prefixPinmode,strlen(prefixPinmode))==0) 
  {
    outPin = atoi(msg+strlen(prefixPinmode));
    if(outPin>=FIRST_DIGITAL_PIN && outPin<=LAST_DIGITAL_PIN) //sanity check
    {
      if(value==0) 
      {
        pinDir[outPin/8] = pinDir[outPin/8] & ~(1<<(outPin%8)); //turn bit in our own direction buffer to off = input
        pinMode(outPin,INPUT); //set DDR register bit to input
        digitalWrite(outPin,HIGH); //reenable pull-up
      } 
      else 
      {
        pinDir[outPin/8] = pinDir[outPin/8] | (1<<(outPin%8)); //turn bit on
        pinMode(outPin,OUTPUT); // turn DDR bit to output
      }
    }
    return;
  }
  //is this a reset message? if so, reinitialize.
  if(strncmp(msg,prefixReset,strlen(prefixReset))==0) 
  {
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
    setup();
  }
}

void WOSC::checkDiscreteInputs() 
{
  int i;
  byte state[NUM_PORTS] = {0x00};
  //WIRING: read all ports into buffer
  for(i=0; i<NUM_PORTS; i++)
  {
    state[i]= portRead(i);
  }

  // if the state of a pin has changed since last time, 
  // and that pin is an input pin, send a message
  for(i=FIRST_DIGITAL_PIN;i<=LAST_DIGITAL_PIN;i++) 
  {
    if(!(pinDir[i/8] & (1<<(i%8))) && (i!=RX_PIN) && (i!=TX_PIN)) //if pin is input and not RX/TX
    { 
      if  ((state[i/8] & (1<<(i%8))) != (inputBuffer[i/8] &(1<<(i%8)))) //does this shift work?
      { 
        strcpy(oscOutAddress,prefixIn);
        char buf[4];
        strcat(oscOutAddress,itoa(i,buf,10));
        sendMessage(oscOutAddress, !(state[i/8] & (1<<(i%8))));
      }
    }
  }

  //save current state to buffer
  for(i=0; i<NUM_PORTS; i++) 
  {
    inputBuffer[i]=state[i];
  }
}

void WOSC::checkAnalogInput(byte channel) 
{
  int result;
  int diff;
  // read a2d
  result = analogRead(channel); // >>2 on arduino

  // compare to last reading - if delta big enough,
  // send message
  //diff = result - a2dBuffer[channel];
  //if(diff>MIN_A2D_DIFF || diff<(int)((-1)*MIN_A2D_DIFF)) {
  if(result!=a2dBuffer[channel])
  {
    a2dBuffer[channel]=result;
    strcpy(oscOutAddress,prefixA2d);
    char buf[4];
    strcat(oscOutAddress,itoa(channel,buf,10));
    sendMessage(oscOutAddress, result);
  }
}

void WOSC::parse(unsigned char c) {
  byte i;
  switch(oscRxNextOp) 
  {
  case OSC_RXOP_WAITFORSTART:
    if(c==0xBE) //0xBE is the magic start byte
    {
      oscRxNextOp = OSC_RXOP_READSIZE;
    }
    break;

  case OSC_RXOP_READSIZE:
    oscRxMsgSize = c; // read message size
    oscRxReadBytes = 0; //reset index into message buffer
    if(oscRxMsgSize < (OSC_MAX_RX_MSG_SIZE-1)) 
    {
      oscRxNextOp = OSC_RXOP_READADDR;
    } 
    else 
    {
      oscRxNextOp = OSC_RXOP_SKIPMSG; //Msg is too long
    }
    break;

  case OSC_RXOP_READADDR:
    if(c!=0 && c!=',') 
    {
      oscRxData[oscRxReadBytes++] = c; //copy normal addr byte
    } 
    else if (c==',') 
    {
      //if we went straight from addr to to tag string, convert "," of tag string to 0x00
      // so our address string is properly zero-terminated
      //and jump ahead in the state machine to read second tag byte next
      oscRxData[oscRxReadBytes++]=0x00;
      oscRxNextOp = OSC_RXOP_READTAGBYTE2;
    }
    else 
    {
      oscRxData[oscRxReadBytes++] = 0;
      if(!((oscRxReadBytes)&0x03)) //skip 0s until we hit byte boundary
      { 
        oscRxNextOp = OSC_RXOP_READTAGBYTE1; 
      } 
    }
    break;

    // read type tag string bytes 1-4
  case OSC_RXOP_READTAGBYTE1:
    oscRxData[oscRxReadBytes++] = c;
    if(c==',') 
    {
      // valid type tag start character found	
      oscRxNextOp = OSC_RXOP_READTAGBYTE2;
    } 
    else 
    {
      // no type tag start char present
      // assume one int arg and read its first byte
      oscRxIntArg1 = 0;
      oscRxIntArg1 |= ((unsigned long)(c) << 0x18);
      oscRxNextOp = OSC_RXOP_READARG1BYTE2;
    }
    break;
  case OSC_RXOP_READTAGBYTE2:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) 
    {
    case 'i': //int32 argument
      oscRxNextOp = OSC_RXOP_READTAGBYTE3;
      break;
      // all other types besides int are not supported yet
      // so skip remainder of message
    case 'f': //float arg
    case 's': //string arg
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
    }
    break;
  case OSC_RXOP_READTAGBYTE3:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) 
    {
      // null - message has only one arg - we're ok
    case 0:
      oscRxNextOp = OSC_RXOP_READTAGBYTE4;
      break;
      // all others: not yet supported; skip rest of message
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
      break;
    }
    break;
  case OSC_RXOP_READTAGBYTE4:
    oscRxData[oscRxReadBytes++] = c;
    switch (c) 
    {
      // null - message has only one arg - we're ok
    case 0:
      oscRxNextOp = OSC_RXOP_READARG1BYTE1;
      break;
      // all others: not yet supported; skip rest of message
    default:
      oscRxNextOp = OSC_RXOP_SKIPMSG;
      break;
    }
    break;

    // read argument bytes 1-4
  case OSC_RXOP_READARG1BYTE1:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 = 0;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x18);
    oscRxNextOp = OSC_RXOP_READARG1BYTE2;
    break;
  case OSC_RXOP_READARG1BYTE2:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x10);
    oscRxNextOp = OSC_RXOP_READARG1BYTE3;
    break;
  case OSC_RXOP_READARG1BYTE3:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= ((unsigned long)(c) << 0x08);
    oscRxNextOp = OSC_RXOP_READARG1BYTE4;
    break;
  case OSC_RXOP_READARG1BYTE4:
    oscRxData[oscRxReadBytes++] = c;
    oscRxIntArg1 |= (unsigned long)(c);
    oscRxNextOp = OSC_RXOP_READCHECKSUM;
    break;

    // read checksum byte; check msg integrity; fire off user function
  case OSC_RXOP_READCHECKSUM:
    // check that we read the right number of bytes
    if (oscRxReadBytes != oscRxMsgSize) 
    {
      sendMessageInt("/error/msgsize/",oscRxReadBytes);
    } 
    else {
      oscRxChecksum = 0;
      for (i=0; i<oscRxMsgSize; i++)
      {
        oscRxChecksum+=oscRxData[i];
      }
      if(oscRxChecksum == c) 
      {
        // checksum matched and we're done with this msg
        // -> fire off user function
        receiveMessageInt(oscRxData,oscRxIntArg1);

      } 
      else 
      {
        // mismatch - throw this message away
        sendMessageInt("/error/checksum",oscRxChecksum);
      }
    }
    // wait for next message header
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
    break;

    //skip rest of message - called if an error was detected in the current 
    //incoming message
  case OSC_RXOP_SKIPMSG:
    if(++oscRxReadBytes == (oscRxMsgSize+1)) 
    {
      oscRxNextOp = OSC_RXOP_WAITFORSTART;
    }
    break;
  default:
    oscRxNextOp = OSC_RXOP_WAITFORSTART;
  }
}