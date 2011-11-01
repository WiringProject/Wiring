/* $Id: WiringBoot.c 1184 2011-06-13 02:57:09Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | Wiring Serial Bootloader for
|| | Atmel megaAVR controllers
|| | using STK500V2 protocol.
|| #
||
|| @notes
|| | Requirements:
|| |   Atmel megaAVR controller with a minimum of 1024 words (2048 bytes)
|| |   of bootloader space and 1 hardware USART.  Debug option may require
|| |   more space.  Rogue SD boot will require 2048 words.
|| |
|| | Various source references:
|| |   stk500boot.c - by Peter Fleury http://jump.to/fleury
|| |   stk500boot.c - by Jason P. Kyle
|| |   Adaboot - http://www.ladyada.net/library/arduino/bootloader.html
|| |   optiboot.c - Optiboot bootloader for Arduino
|| |   Atmel Application Notes: AVR109 (self-programming),
|| |                            AVR068 (STK500v2 protocol)
|| |
|| | Configuration checklist:
|| |
|| |   F_CPU
|| |   BOOT_PROTOCOL - one of BOOT_STK500V1, BOOT_STK500V2
|| |   BOOT_SIZE - size of bootloader area
|| |   BOOT_ADDRESS - start address of bootloader (in hex)
|| |   BOOT_USART - [0-n] - Hardware USART for serial programming
|| |   BOOT_BAUD_RATE
|| |   SERIAL_TIMEOUT - Time in seconds before exiting bootloader
|| |   NUM_LED_FLASHES
|| |   LED_PORT
|| |   LED_PIN
|| |   LED_FLASH_TIME (in milliseconds)
|| |   (optional) LEDInitialize(), LEDOn(), LEDOff()
|| |   (optional) LEDRXInitialize(), LEDRXOn(), LEDRXOff()
|| |   (optional) LEDTXInitialize(), LEDTXOn(), LEDTXOff()
|| |   DEBUG
|| |   (optional) DEBUG_USART
|| |   (optional) DEBUG_BAUD_RATE
|| |
|| | TODO:
|| |   SOFT_PORT for BOOT_USART
|| |   Configuration for SDBOOT using Rogue Robotics SD modules
|| #
||
|| @license Please see License.txt for license information.
||
*/

#include "WiringBoot.h"

#include "stk500v2.h"


/*
#if defined (BOOT_STK500V2)
 #include "stk500v2.h"
#elif defined (BOOT_STK500V1)
 #include "stk500v1.h"
#else
 #error "No bootloader protocol selected"
#endif
*/



/*
  MCU initialization routine

  Since we have dispensed with the interrupt vectors,
  __do_clear_bss() (which zeroes all global variables),
  and __do_copy_data() (which initializes all variables
  with with static data - like predefined arrays, etc),
  we need this routine to initialize the important bits of the MCU.
  The stack pointer (most newer AVR's are HARDWARE initialized
  to RAMEND, so this is just in case we are using an older AVR), and
  clear the zero register (r1, which is expected to be zero all the time).

  If you use this sort of concept in your code, make sure you initialize
  your globals inside main() if you remove __do_copy_data().

  Notes:
    naked attribute: no entry/exit code (stack push/pop)
    section(".vectors"): places code at the start of the vector table
      (effectively removing the interrupt vector table)

*/

// Prevent data setup functions being linked from libgcc.a
//__attribute__((naked)) void __do_copy_data(){}
__attribute__((naked)) void __do_clear_bss(){}

int main(void) __attribute__ ((naked));

void __jumpMain(void) __attribute__((naked, section (".vectors")));
void __jumpMain(void)
{
  asm("clr __zero_reg__");        // clear r1
  SREG = 0;                       // clear status register
  SP = RAMEND;                    // set stack pointer
  asm volatile ("rjmp main");     // jump to main()
}


void app_start(void) __attribute__ ((naked));
void app_start(void)
{
  // Jump to reset vector - quick and common way to get to the app section

  // LOTS of different methods
  // Direct jump - Problem, avr-gcc may not produce long address for >128K parts

  //  asm volatile ("jmp 0x0");


  // Try an indirect jump - >128K parts... avr-gcc still not up to snuff
  // e.g. (eijmp not defined in assembler as of 4.3.2)
  
  //  __asm__ __volatile__ (
  //    "clr r30\n"
  //    "clr r31\n"
  //#ifdef EIND
  //    "clr eind\n"
  //    "eijmp\n"
  //#else
  //    "ijmp\n"
  //#endif
  //  );


  // let's return the MCU to initial state, as much as we can
#ifdef HW_SDBOOT_CHECK_PORT
  HW_SDBOOT_CHECK_PORT = 0;
  *(PORT_TO_DDR(HW_SDBOOT_CHECK_PORT)) = 0;
#endif
#ifdef LED_PORT
  LED_PORT = 0;
  *(PORT_TO_DDR(LED_PORT)) = 0;
#endif
#ifdef LED_RX_PORT
  LED_RX_PORT = 0;
  *(PORT_TO_DDR(LED_RX_PORT)) = 0;
#endif
#ifdef LED_TX_PORT
  LED_TX_PORT = 0;
  *(PORT_TO_DDR(LED_TX_PORT)) = 0;
#endif

  // How about using a return?
  // Three bytes on the stack for the controllers >128K bytes (64K words)
  asm (
    "push r1\n"
    "push r1\n"
    "push r1\n"
    "ret\n"
  );
  for (;;);
}


/*************************************************************************/
// Misc. Routines
/*************************************************************************/

#if (NUM_LED_FLASHES > 0)
void flash_led(uint8_t count)
{
  while (count--)
  {
    LEDOn();
    _delay_ms(LED_FLASH_TIME);
    LEDOff();
    _delay_ms(LED_FLASH_TIME);
  }
}
#else
 #define flash_led(x)
#endif


/*************************************************************************/
// Debug Routines
/*************************************************************************/

#ifdef DEBUG
void debug_printNumber(int32_t n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
  uint8_t i = 0;

  if (n == 0)
  {
    debug_serial_putch('0');
    return;
  } 

  if (n < 0)
  {
    debug_serial_putch('-');
    n = -n;
  }
  
  while (n > 0)
  {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    debug_serial_putch((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}


void debugstr_P(uint_flashptr_t s)
{
  register uint8_t c;

  while ((c = P_read_byte(s++)))
    debug_serial_putch(c);
}

#else

#define debug_printNumber(x)
#define debugstr_P(x)

#endif


/*************************************************************************/
// Serial Routines
/*************************************************************************/

uint8_t boot_serial_getchTimeout(void)
{
  uint32_t count = 0;

  LEDRXOn();

  while (!boot_serial_available())
  {
    count++;

    if (count > MAX_TIME_COUNT)
    {
      debugstr_P(GET_FAR_ADDRESS(PSTRU("T.O. Starting app\r")));

      app_start();
    }
  }

  LEDRXOff();

  return boot_serial_getch();
}

/*
void boot_serial_putstr_P(uint_flashptr_t str)
{
  register uint8_t c;

  LEDTXOn();

  while ((c = P_read_byte(str++)))
    boot_serial_putch(c);

  LEDTXOff();
}
*/

/*
void boot_serial_getNch(uint8_t count)
{
  LEDRXOn();

  while (count--)
    boot_serial_getch();

  LEDRXOff();
}
*/


/*************************************************************************/
// Main Routine
/*************************************************************************/

int main(void)
{
  uint8_t mcusr;

  // Reset source detector - if not external reset, jump to the app.
  // Concept: ALWAYS enter the bootloader on external reset, but if
  // we get a watchdog or other reset, fall through to the app.
  // (If the user gets into the WD reset loop, they can still upload
  // new code because the bootloader will always start on an external reset,
  // as the WD is not running after an external reset/power-up.)

  mcusr = MCUSR;
  MCUSR = 0;

  if (!(mcusr & ((1 << EXTRF) | (1 << PORF))))
    app_start();

  boot_serial_init();
  boot_serial_setBitrate(BOOT_BAUD_RATE);

  debug_serial_init();
  debug_serial_setBitrate(9600);

  LEDInitialize();
  LEDRXInitialize();
  LEDTXInitialize();

  flash_led(NUM_LED_FLASHES);

  debugstr_P(GET_FAR_ADDRESS(PSTRU("Serial Bootloader starting\r")));


/*
#if defined (BOOT_STK500V2)
  stk500v2loader();
#elif defined (BOOT_STK500V1)
  stk500v1loader();
#elif defined (BOOT_OTHER)
  loader();
#endif
*/

  stk500v2loader();

  app_start();

  for (;;);
}

