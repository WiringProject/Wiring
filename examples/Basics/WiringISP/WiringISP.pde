/**
 * STK500V2 compatible sketch, to program Atmel AVR 8 bit targets via ISP.
 * Copyright (C) 2011 Brett Hagman
 * http://www.roguerobotics.com/
 * bhagman@roguerobotics.com
 * 
 * Please see License.txt for license information.
 * Influential work by Peter Fleury (stk500boot.c).
 * 2006 - Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
 * Some ISP functions from Randall Bohn.
 * AVR NOTES:
 * Atmel Application Note AVR109 - Self-programming
 * Atmel Application Note AVR068 - STK500v2 Protocol
 * NOTES FOR USAGE:
 * The HOST board is defined as the board used as programmer or the board
 * that will run this sketch. The TARGET board is defined as the board to
 * be programmed with a new bootloader.
 * On the HOST board connect pins MISO, MOSI and SCK to the TARGET
 * MISO, MOSI and SCK, then connect the HOST SS pin to the
 * RESET pin on the target board.
 * To program a bootloader on a Wiring v1.x board:
 * When using a Wiring v1.x board as a TARGET board (atmega128, atmega1281 and
 * atmega2561 processors), connect the HOST board pins to the Wiring v1 board 6 pin ISP
 * connector for easiness or remember that the programming pins (as a TARGET board)
 * for this type of board are different: MOSI is pin 32 PE0 and MISO is pin 33 PE1
 */

#include "stk500v2_constants.h"

typedef uint16_t address_t;

#define LEDPIN          WLED

#define BAUDRATE        115200

#define RESET           SS

#define LED_HB          9
#define LED_ERR         8
#define LED_PMODE       7


// HW and SW version, reported to AVRISP, must match version of AVRStudio

#define CONFIG_PARAM_BUILD_NUMBER_LOW   0
#define CONFIG_PARAM_BUILD_NUMBER_HIGH  0
#define CONFIG_PARAM_HW_VER             0x0F
#define CONFIG_PARAM_SW_MAJOR           2
#define CONFIG_PARAM_SW_MINOR           0x0A


// States used in the receive state machine

#define ST_START        0
#define ST_GET_SEQ_NUM  1
#define ST_MSG_SIZE_1   2
#define ST_MSG_SIZE_2   3
#define ST_GET_TOKEN    4
#define ST_GET_DATA     5
#define ST_GET_CHECK    6
#define ST_PROCESS      7



// ****************************************************************************
// Support functions
// ****************************************************************************

/*
void heartbeat(void)
{
  static uint8_t state = 0;
  static uint32_t timeref = 0;

  if ((millis() - timeref) > HB_TIME)
  {
    state = !state;
    digitalWrite(LED_HB, state);
    timeref = millis();
  }
}
*/

uint8_t getByte(void)
{
  while (!Serial.available());

  return Serial.read();
}

#define sendByte(c) Serial.write(c)

void spi_init(void)
{
  uint8_t x;

//  SPCR = 0x53;
  // SPIE = Interrupt disabled
  // SPE  = SPI Enable
  // DORD = MSB first
  // MSTR = Master mode
  // CPOL = Non-inverted
  // CPHA = sample/setup
  // SPR1, SPR0 = ck/128 (0b11)
  SPCR = 0b01010011;
  x = SPSR;
  x = SPDR;
}


void spi_wait(void)
{
  while (!(SPSR & (1 << SPIF)));
}


uint8_t spi_send(uint8_t b)
{
  uint8_t reply;

  SPDR = b;
  spi_wait();
  reply = SPDR;

  return reply;
}


uint8_t spi_transaction(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
  spi_send(a);
  spi_send(b);
  spi_send(c);
  return spi_send(d);
}


// ****************************************************************************
// SPI programming functions
// ****************************************************************************


void end_pmode(void)
{
  SPCR = 0;  // disable SPI

  // release all of the pins
  pinMode(MISO, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(RESET, INPUT);
}

/*
uint8_t start_pmode() {
  spi_init();
  // following delays may not work on all targets...
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);
  pinMode(SCK, OUTPUT);
  digitalWrite(SCK, LOW);
  delay(50);
  digitalWrite(RESET, LOW);
  delay(50);
  pinMode(MISO, INPUT);
  pinMode(MOSI, OUTPUT);
  spi_transaction(0xAC, 0x53, 0x00, 0x00);
  return 1;
}
*/

uint8_t start_pmode(void)
{
  uint8_t reply;
  uint8_t attempts = 4;

  pinMode(SCK, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(MOSI, OUTPUT);
  spi_init();
  // digitalWrite(SCK, LOW);      // When CPOL = 0, SCK idles low
  digitalWrite(RESET, HIGH);      // Let's leave RESET high for now
  digitalWrite(MISO, HIGH);       // Set the internal pull-up on MISO
  // digitalWrite(MOSI, HIGH);    // MOSI is controlled by the SPI

  while (attempts--)
  {
    // To enter serial programming on Atmel parts:
    // Set SCK and RESET low
    // wait at least 20 ms
    // send "Programming Enable" serial instruction
    digitalWrite(RESET, LOW);
    delay(40);

    spi_send(0xAC);
    spi_send(0x53);
    reply = spi_send(0x00);
    spi_send(0x00);

    if (reply == 0x53)
      return 1;
    else
    {
      digitalWrite(RESET, HIGH);
      delay(10);
    }
  }
  end_pmode();
  return 0;
}


// ****************************************************************************
// setup/loop
// ****************************************************************************

void setup()
{
  Serial.begin(BAUDRATE);
  pinMode(LEDPIN, OUTPUT);
}


// ****************************************************************************
// STK500 V2 protocol function
// ****************************************************************************

//void stk500v2loader(void)
void loop(void)
{
  uint8_t     msgParseState;
  uint16_t    i = 0;
  uint8_t     checksum = 0;
  uint16_t    msgLength = 0;
  uint8_t     msgBuffer[285];
  uint8_t     c, *p;
  uint8_t     seqNum = 0;
  uint8_t     param_controller_init = 0;
  address_t   address = 0;


  while (1)
  {
    /*
     * Collect received bytes to a complete message
     */
    msgParseState = ST_START;

    digitalWrite(LEDPIN, HIGH);

    while (msgParseState != ST_PROCESS)
    {
      c = getByte();

      switch (msgParseState)
      {
        case ST_START:
          if (c == MESSAGE_START)
          {
            msgParseState = ST_GET_SEQ_NUM;
            checksum = MESSAGE_START ^ 0;
          }
          break;

        case ST_GET_SEQ_NUM:
          if ((c == 1) || (c == seqNum))
          {
            seqNum = c;
            msgParseState = ST_MSG_SIZE_1;
            checksum ^= c;
          }
          else
          {
            msgParseState = ST_START;
          }
          break;

        case ST_MSG_SIZE_1:
          msgLength = (unsigned int) c << 8;
          msgParseState = ST_MSG_SIZE_2;
          checksum ^= c;
          break;

        case ST_MSG_SIZE_2:
          msgLength |= c;
          msgParseState = ST_GET_TOKEN;
          checksum ^= c;
          break;

        case ST_GET_TOKEN:
          if (c == TOKEN)
          {
            msgParseState = ST_GET_DATA;
            checksum ^= c;
            i = 0;
          }
          else
          {
            msgParseState = ST_START;
          }
          break;

        case ST_GET_DATA:
          msgBuffer[i++] = c;
          checksum ^= c;
          if (i == msgLength)
            msgParseState = ST_GET_CHECK;
          break;

        case ST_GET_CHECK:
          if (c == checksum)
            msgParseState = ST_PROCESS;
          else
            msgParseState = ST_START;
          break;
      } // switch
    } // while (msgParseState)

    digitalWrite(LEDPIN, LOW);

    /*
     * Now process the STK500 commands, see Atmel Appnote AVR068
     */

    switch (msgBuffer[0])
    {
      case CMD_SPI_MULTI:
        {
          uint8_t numTX = msgBuffer[1];
          uint8_t numRX = msgBuffer[2];
          uint8_t RXstart = msgBuffer[3];
          uint8_t *t = msgBuffer + 4;

          msgLength = numRX + 3;
          p = msgBuffer + 1;

          *p++ = STATUS_CMD_OK;

          for (i = 0; i < numTX; i++)
          {

            if (numRX && (i >= RXstart))
            {
              *p++ = spi_send(*t++);
              numRX--;
            }
            else
              spi_send(*t++);
          }

          *p++ = STATUS_CMD_OK;
        }
        break;

      case CMD_SIGN_ON:
        msgLength = 11;
        msgBuffer[1]  = STATUS_CMD_OK;
        msgBuffer[2]  = 8;
        msgBuffer[3]  = 'S';
        msgBuffer[4]  = 'T';
        msgBuffer[5]  = 'K';
        msgBuffer[6]  = '5';
        msgBuffer[7]  = '0';
        msgBuffer[8]  = '0';
        msgBuffer[9]  = '_';
        msgBuffer[10] = '2';
        break;

      case CMD_SET_PARAMETER:
        if (msgBuffer[1] == PARAM_CONTROLLER_INIT)
          param_controller_init = msgBuffer[4];
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_GET_PARAMETER:
        {
          unsigned char value;

          switch (msgBuffer[1])
          {
            case PARAM_BUILD_NUMBER_LOW:
              value = CONFIG_PARAM_BUILD_NUMBER_LOW;
              break;
            case PARAM_BUILD_NUMBER_HIGH:
              value = CONFIG_PARAM_BUILD_NUMBER_HIGH;
              break;
            case PARAM_HW_VER:
              value = CONFIG_PARAM_HW_VER;
              break;
            case PARAM_SW_MAJOR:
              value = CONFIG_PARAM_SW_MAJOR;
              break;
            case PARAM_SW_MINOR:
              value = CONFIG_PARAM_SW_MINOR;
              break;
            case PARAM_CONTROLLER_INIT:
              value = param_controller_init;
              break;
            case PARAM_SCK_DURATION:
              value = 2;
              break;
            default:
              value = 0;
              break;
          }
          msgLength = 3;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = value;
        }
        break;

      case CMD_ENTER_PROGMODE_ISP:
        msgLength = 2;
        if (start_pmode())
          msgBuffer[1] = STATUS_CMD_OK;
        else
          msgBuffer[1] = STATUS_CMD_FAILED;
        break;

      case CMD_LEAVE_PROGMODE_ISP:
        end_pmode();
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_READ_FUSE_ISP:
      case CMD_READ_LOCK_ISP:
      case CMD_READ_SIGNATURE_ISP:
        // we'll ignore the pollIndex @ msgBuffer[1], since the low level command always sends
        // the return value on the 4th byte.
        msgLength = 4;
        msgBuffer[1] = STATUS_CMD_OK;
        msgBuffer[2] = spi_transaction(msgBuffer[2], msgBuffer[3], msgBuffer[4], msgBuffer[5]);
        msgBuffer[3] = STATUS_CMD_OK;
        break;

      case CMD_PROGRAM_FUSE_ISP:
      case CMD_PROGRAM_LOCK_ISP:
        spi_transaction(msgBuffer[1], msgBuffer[2], msgBuffer[3], msgBuffer[4]);
        msgLength = 3;
        msgBuffer[1] = STATUS_CMD_OK;
        msgBuffer[2] = STATUS_CMD_OK;
        break;

      case CMD_CHIP_ERASE_ISP:
        // most devices will complete the chip erase in 9.0 ms.
        spi_transaction(0xAC, 0x80, 0, 0);
        delay(40);
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_LOAD_ADDRESS:
        // In the STK500 Specification (Ver 2.0), CMD_LOAD_ADDRESS:
        // "For word-addressed memories (program flash),
        //  the Address parameter is the word address"
        // Since the avr-libc boot.h functions require a byte address,
        // we need to shift the flash word address by one bit to get
        // the byte address.
        // EEPROM addresses (which are sent as byte addresses) stay as-is.

        address = (((address_t) msgBuffer[3]) << 8) | msgBuffer[4];

        // If bit 31 of address is set, then:
        // "This is an indication to STK500 that a load extended
        // address must be executed."
        if (msgBuffer[1] & 0x80)
        {
          // The extended address is in msgBuffer[2].
          // > 64K words, will be 1,
          // > 128K words, will be 2, etc
          spi_transaction(0x4d, 0, msgBuffer[2], 0);
        }

        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_PROGRAM_FLASH_ISP:
      case CMD_PROGRAM_EEPROM_ISP:
        {
          uint16_t byteCount = (((uint16_t) msgBuffer[1]) << 8) | msgBuffer[2];

          p = msgBuffer + 10;

          if (msgBuffer[0] == CMD_PROGRAM_FLASH_ISP)
          {
            // TODO: Check the mode byte for write mode.
            // The majority of devices we will program will use page mode,
            // so that's what we'll focus on here.
            // We will ignore the different delay/polling methods, and
            // use a delay.
            // Also, we are ignoring, for now, the "Write Page" bit of the
            // mode byte, which is in place to accommodate page sizes
            // larger than what can be buffered.
            //if (msgBuffer[3] & 0x01)

            // Page mode - load into page buffer then write the page.
            for (i = 0; i < (byteCount >> 1); i++)
            {
              /// i is a word address within the page buffer
              spi_transaction(0x40, 0, i, *p++);
              spi_transaction(0x48, 0, i, *p++);
            }

            spi_transaction(0x4c, (uint8_t)(address >> 8), (uint8_t) address, 0);
            // Most parts will write flash within 5 ms
            delay(10);
            address += (byteCount >> 1);
          }
          else
          {
            // CMD_PROGRAM_EEPROM_ISP
            for (i = 0; i < byteCount; i++)
            {
              spi_transaction(0xc0, (uint8_t)(address >> 8), (uint8_t) address, *p++);
              // Most parts will write flash within 10 ms
              delay(20);
              address += byteCount;
            }
          }
          msgLength = 2;
          msgBuffer[1] = STATUS_CMD_OK;
        }
        break;

      case CMD_READ_FLASH_ISP:
      case CMD_READ_EEPROM_ISP:
        {
          uint16_t byteCount = (((uint16_t) msgBuffer[1]) << 8) | msgBuffer[2];

          p = msgBuffer + 1;

          *p++ = STATUS_CMD_OK;

          if (msgBuffer[0] == CMD_READ_FLASH_ISP)
          {
            for (i = 0; i < byteCount; i += 2)
            {
              *p++ = spi_transaction(0x20, (uint8_t)(address >> 8), (uint8_t) address, 0);
              *p++ = spi_transaction(0x28, (uint8_t)(address >> 8), (uint8_t) address, 0);
              address++;
            }
          }
          else
          {
            // CMD_READ_EEPROM_ISP
            for (i = 0; i < byteCount; i++)
            {
              *p++ = spi_transaction(0xa0, (uint8_t)(address >> 8), (uint8_t) address, 0);
              address++;
            }
          }

          *p++ = STATUS_CMD_OK;
          msgLength = byteCount + 3;
        }
        break;

      default:
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_FAILED;
        break;
    }

    /*
     * Now send answer message back
     */

    digitalWrite(LEDPIN, HIGH);

    sendByte(MESSAGE_START);
    checksum = MESSAGE_START ^ 0;

    sendByte(seqNum);
    checksum ^= seqNum;

    c = ((msgLength >> 8) & 0xFF);
    sendByte(c);
    checksum ^= c;

    c = msgLength & 0x00FF;
    sendByte(c);
    checksum ^= c;

    sendByte(TOKEN);
    checksum ^= TOKEN;

    p = msgBuffer;
    while (msgLength)
    {
      c = *p++;
      sendByte(c);
      checksum ^= c;
      msgLength--;
    }
    sendByte(checksum);
    seqNum++;

    digitalWrite(LEDPIN, LOW);

  }
}

