/* $Id: OSC.h 1198 2011-06-14 21:08:27Z bhagman $
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

#ifndef OSC_h
#define OSC_h

#include <Wiring.h>

#define MIN_A2D_DIFF 4  // threshold for reporting a2d changes
#define MAX_LENGTH 24   // size of buffer for building WOSC msgs
#define OSC_SERIAL_SPEED 38400

#define FIRST_DIGITAL_PIN 0 
#define LAST_DIGITAL_PIN (TOTAL_PINS - 1)
#define NUM_DIGITAL_PINS TOTAL_PINS
#define NUM_PORTS WIRING_PORTS

//#define FIRST_ANALOG_PIN FIRST_ANALOG_PIN
#define LAST_ANALOG_PIN (FIRST_ANALOG_PIN + TOTAL_ANALOG_PINS - 1)
#define NUM_ANALOG_PINS TOTAL_ANALOG_PINS
#define RX_PIN RX0
#define TX_PIN TX0

// define state constants for parsing FSM
#define OSC_RXOP_WAITFORSTART 0
#define OSC_RXOP_READSIZE 1
#define OSC_RXOP_READADDR 2
#define OSC_RXOP_READTAG 3
#define OSC_RXOP_READARG 4
#define OSC_RXOP_READCHECKSUM 5
//removed READMSG
#define OSC_RXOP_SKIPMSG 7
#define OSC_RXOP_READARG1BYTE1 8
#define OSC_RXOP_READARG1BYTE2 9
#define OSC_RXOP_READARG1BYTE3 10
#define OSC_RXOP_READARG1BYTE4 11
#define OSC_RXOP_READTAGBYTE1 12
#define OSC_RXOP_READTAGBYTE2 13
#define OSC_RXOP_READTAGBYTE3 14
#define OSC_RXOP_READTAGBYTE4 15
#define OSC_MAX_RX_MSG_SIZE 32


class WOSC 
{
public:
  WOSC(Stream &s);
  
  void begin();
  void transmit();
  void sendMessage(char *address, unsigned long value);
    
  
private:
  void checkDiscreteInputs();
  void checkAnalogInput(byte k);
  void sendMessageInt(char * address, unsigned long value);
  void receiveMessageInt(char * msg, unsigned long value);
  void parse(unsigned char c);
  
  static const char prefixReport[9];// = "/report/";
  static const char prefixPinmode[11];// = "/pinmode/";
  static const char prefixOut[6];// = "/out/";
  static const char prefixPwm[6];// = "/pwm/";
  static const char prefixIn[5];//="/in/";
  static const char prefixA2d[6];//="/adc/";
  static const char prefixReset[7];//="/reset"; //TODO: implement
//  static const byte pwmPinMap[6];
  
  Stream *stream;
  //////parser variables////////
  byte oscRxNextOp; //keeps track of current state
  // space for buffer in RAM
  char oscRxData[OSC_MAX_RX_MSG_SIZE];
  
  byte oscRxMsgSize; // size of incoming msg
  byte oscRxReadBytes; //number of bytes read
  byte *oscRxAddr;
  unsigned long oscRxIntArg1; //int argument of message
  byte oscRxChecksum;
  char oscBuffer[MAX_LENGTH]; // holds outgoing WOSC message
  
  // which values should be reported?
  byte reportAnalog; //bitmask - 0=off, 1=on - default:all off 
  boolean reportDigital; //no per-pin reporting for analog

  int incomingByte;	// for incoming serial data
  int k;

  int a2dBuffer[NUM_ANALOG_PINS];   // holds previous A2D conversion values
  byte inputBuffer[NUM_PORTS]; // holds previous values of PORTB and PORTD (pins 0..7); start all high because of pull-ups
  byte pinDir[NUM_PORTS]; //buffer that saves pin directions 0=input; 1=output; default: all in

  char oscOutAddress[10]; //string that holds outgoing osc message address
};

extern WOSC OSC;

#endif
