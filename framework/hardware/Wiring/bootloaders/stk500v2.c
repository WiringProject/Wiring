/* $Id: stk500v2.c 1153 2011-06-07 00:51:12Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| |
|| | STK500v2 Compatible bootloader routine.
|| | Functions/macros to facilitate parts >64K words (128K bytes).
|| |
|| #
||
|| @notes
|| |
|| | If no command is received (while in command acceptance state) within
|| | the timeout (defined within the boot_serial_getchTimeout() function,
|| | the routine will return to the calling application.
|| |
|| | Use Auto Programming mode (in AVR Studio) to program both flash and eeprom,
|| | otherwise bootloader will exit after flash programming.
|| |
|| | Various source references:
|| |   stk500boot.c - by Peter Fleury http://jump.to/fleury
|| |   stk500boot.c - by Jason P. Kyle
|| |   Atmel Application Notes: AVR109 (self-programming),
|| |                            AVR068 (STK500v2 protocol)
|| |
|| #
||
|| @license Please see License.txt for license information.
||
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>

#include "stk500v2-constants.h"
#include "WiringBoot.h"

// Because we make this alias, ENABLE_LEAVE_BOOTLOADER below is meaningless
#define getByte() boot_serial_getchTimeout()
#define sendByte(c) boot_serial_putch(c)


// BUG FIX: avr-libc uses signature from '644 for '644P (libc ver 09/03/13)
#if defined (__AVR_ATmega644P__)
 #if SIGNATURE_2 != 0x0A
  #warning "FIXME: avr-libc uses signature from '644 for '644P (libc ver 09/03/13)"
  #undef SIGNATURE_2
  #define SIGNATURE_2 0x0A
 #endif
#endif


/*
 * Comment the following lines to save code space
 */
//#define ENABLE_PROGRAM_LOCK_BIT_SUPPORT       // enable program lock bits

/*
 *  Uncomment to leave bootloader and jump to application after programming.
 */
#define ENABLE_LEAVE_BOOTLOADER


/*
 * HW and SW version, reported to AVRISP, must match version of AVRStudio
 */
#define CONFIG_PARAM_BUILD_NUMBER_LOW   0
#define CONFIG_PARAM_BUILD_NUMBER_HIGH  0
#define CONFIG_PARAM_HW_VER             0x0F
#define CONFIG_PARAM_SW_MAJOR           2
#define CONFIG_PARAM_SW_MINOR           0x0A


/*
 * States used in the receive state machine
 */
#define ST_START        0
#define ST_GET_SEQ_NUM  1
#define ST_MSG_SIZE_1   2
#define ST_MSG_SIZE_2   3
#define ST_GET_TOKEN    4
#define ST_GET_DATA     5
#define ST_GET_CHECK    6
#define ST_PROCESS      7


/*
 * use 16bit address variable for ATmegas with <= 64K flash
 */
#if defined (RAMPZ)
typedef uint32_t address_t;
#else
typedef uint16_t address_t;
#endif


void stk500v2loader(void)
{
  address_t       address = 0;
//  address_t       eraseAddress = 0;
  unsigned char   msgParseState;
  unsigned int    i = 0;
  unsigned char   checksum = 0;
  unsigned char   seqNum = 0;
  unsigned int    msgLength = 0;
  unsigned char   msgBuffer[285];
  unsigned char   c, *p;
  unsigned char   isLeave = 0;


  while (!isLeave)
  {
    /*
     * Collect received bytes to a complete message
     */
    msgParseState = ST_START;
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

    /*
     * Now process the STK500 commands, see Atmel Appnote AVR068
     */

    switch (msgBuffer[0])
    {
      case CMD_SPI_MULTI:
        {
          unsigned char answerByte = 0;

          // only Read Signature Bytes implemented, return dummy value for other instructions
          if (msgBuffer[4]== 0x30)
          {
            unsigned char signatureIndex = msgBuffer[6];

            if (signatureIndex == 0)
              answerByte = SIGNATURE_0;
            else if (signatureIndex == 1)
              answerByte = SIGNATURE_1;
            else
              answerByte = SIGNATURE_2;
          }
          msgLength = 7;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = 0;
          msgBuffer[3] = msgBuffer[4];          // Instruction Byte 1
          msgBuffer[4] = msgBuffer[5];          // Instruction Byte 2
          msgBuffer[5] = answerByte;
          msgBuffer[6] = STATUS_CMD_OK;
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
            default:
              value = 0;
              break;
          }
          msgLength = 3;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = value;
        }
        break;

      case CMD_LEAVE_PROGMODE_ISP:
#ifdef ENABLE_LEAVE_BOOTLOADER
        isLeave = 1;
#endif
      case CMD_ENTER_PROGMODE_ISP:
      case CMD_SET_PARAMETER:
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_READ_SIGNATURE_ISP:
        {
          unsigned char signatureIndex = msgBuffer[4];
          unsigned char signature;

          if (signatureIndex == 0)
              signature = SIGNATURE_0;
          else if (signatureIndex == 1)
              signature = SIGNATURE_1;
          else
              signature = SIGNATURE_2;

          msgLength = 4;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = signature;
          msgBuffer[3] = STATUS_CMD_OK;
        }
        break;

      case CMD_READ_LOCK_ISP:
        msgLength = 4;
        msgBuffer[1] = STATUS_CMD_OK;
        msgBuffer[2] = boot_lock_fuse_bits_get(GET_LOCK_BITS);
        msgBuffer[3] = STATUS_CMD_OK;
        break;

      case CMD_READ_FUSE_ISP:
        {
          unsigned char fuseBits;

          // command:
          // 0x50 0x00 = low fuse bits
          // 0x58 0x08 = high fuse bits
          // 0x50 0x00 = extended fuse bits
          if (msgBuffer[2] == 0x50)
          {
            if (msgBuffer[3] == 0x08)
              fuseBits = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
            else
              fuseBits = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
          }
          else
          {
            fuseBits = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
          }
          msgLength = 4;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = fuseBits;
          msgBuffer[3] = STATUS_CMD_OK;
        }
        break;

#ifdef ENABLE_PROGRAM_LOCK_BIT_SUPPORT
      case CMD_PROGRAM_LOCK_ISP:
        {
          unsigned char lockBits = msgBuffer[4];

          lockBits = (~lockBits) & 0x3C;        // mask BLBxx bits
          boot_lock_bits_set(lockBits);         // and program it
          boot_spm_busy_wait();

          msgLength = 3;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = STATUS_CMD_OK;
        }
        break;
#endif
/*
      case CMD_CHIP_ERASE_ISP:
        eraseAddress = 0;
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;
*/

      case CMD_LOAD_ADDRESS:
        // In the STK500 Specification (Ver 2.0), CMD_LOAD_ADDRESS:
        // "For word-addressed memories (program flash),
        //  the Address parameter is the word address"
        // Since the avr-libc boot.h functions require a byte address,
        // we need to shift the flash word address by one bit to get
        // the byte address.
        // EEPROM addresses (which are sent as byte addresses) stay as-is.

#if defined (RAMPZ)
        address = (((address_t)(msgBuffer[1]) << 24) |
                   ((address_t)(msgBuffer[2]) << 16) |
                   ((address_t)(msgBuffer[3]) << 8)  |
                               (msgBuffer[4]));
#else
        address = (((msgBuffer[3]) << 8) |
                    (msgBuffer[4]));
#endif
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_PROGRAM_FLASH_ISP:
      case CMD_PROGRAM_EEPROM_ISP:
        {
          unsigned int  size = (((unsigned int) msgBuffer[1]) << 8) | msgBuffer[2];
          unsigned char *p = msgBuffer+10;
          unsigned int  data;
          unsigned char highByte, lowByte;
          address_t     tempAddress;

          if (msgBuffer[0] == CMD_PROGRAM_FLASH_ISP)
          {
            // erase only main section (bootloader protection)
/*
            if (eraseAddress < BOOTLOADER_ADDRESS)
            {
              boot_page_erase(eraseAddress);    // Perform page erase
              boot_spm_busy_wait();             // Wait until the memory is erased.
              eraseAddress += SPM_PAGESIZE;     // point to next page to be erase
            }
*/
            // Erase first
            tempAddress = address << 1;

            boot_page_erase(tempAddress);
            boot_spm_busy_wait();

            /* Write FLASH */
            do
            {
              lowByte   = *p++;
              highByte  = *p++;

              data = (highByte << 8) | lowByte;
              boot_page_fill(address << 1, data);  // expects byte addresses

              address++;                        // Select next word in memory
              size -= 2;                        // Reduce number of bytes to write by two
            } while(size);                      // Loop until all bytes written

            boot_page_write(tempAddress);
            boot_spm_busy_wait();
            boot_rww_enable();                  // Re-enable the RWW section
          }
          else
          {
            /* write EEPROM */
            do
            {
              eeprom_write_byte((uint8_t *)(uint16_t) address, *p);
              p++;
              address++;                        // Select next EEPROM byte
              size--;                           // Decrease number of bytes to write
            } while(size);                      // Loop until all bytes written
          }
          msgLength = 2;
          msgBuffer[1] = STATUS_CMD_OK;
        }
        break;

      case CMD_READ_FLASH_ISP:
      case CMD_READ_EEPROM_ISP:
        {
          uint16_t size = (((uint16_t) msgBuffer[1]) << 8) | msgBuffer[2];
          uint8_t *p = msgBuffer+1;
          msgLength = size + 3;
          address_t byteAddress;

          *p++ = STATUS_CMD_OK;
          if (msgBuffer[0] == CMD_READ_FLASH_ISP)
          {
            uint16_t data;

            // Read FLASH
            do
            {
              byteAddress = address << 1;       // expects byte addresses
#if defined (RAMPZ)
              data = pgm_read_word_far(byteAddress);
#else
              data = pgm_read_word_near(byteAddress);
#endif
              *p++ = (uint8_t) data;            // LSB
              *p++ = (uint8_t) (data >> 8);     // MSB
              address++;                        // Select next word in memory
              size -= 2;
            } while (size);
          }
          else
          {
            /* Read EEPROM */
            do
            {
              *p = eeprom_read_byte((uint8_t *)(uint16_t)address);
              p++;
              address++;                        // Select next EEPROM byte
              size--;
            } while (size);
          }
          *p++ = STATUS_CMD_OK;
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

    LEDTXOn();

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

    LEDTXOff();

  } // while (!isLeave)

  // Now we exit (if we can leave the while loop)
}
