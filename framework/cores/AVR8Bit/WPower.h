/* $Id: WPower.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Power management utility functions for
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WPOWER_H
#define WPOWER_H

#include <Wiring.h>

/* 
 * Power management
 */
static inline void enablePower(uint8_t) __attribute__((always_inline, unused));
static inline void enablePower(uint8_t P)
{
  switch(P)
  {
    case POWER_ADC:
#if defined power_adc_enable
      power_adc_enable();
#endif
      break;
    case POWER_SPI:
#if defined power_spi_enable
      power_spi_enable();
#endif
      break;
    case POWER_WIRE:
#if defined power_twi_enable
      power_twi_enable();
#endif
      break;
    case POWER_TIMER0:
#if defined power_timer0_enable
      power_timer0_enable();
#endif
      break;
    case POWER_TIMER1:
#if defined power_timer1_enable
      power_timer1_enable();
#endif
      break;
    case POWER_TIMER2:
#if defined power_timer2_enable
      power_timer2_enable();
#endif
      break;
    case POWER_TIMER3:
#if defined power_timer3_enable
      power_timer3_enable();
#endif
      break;
    case POWER_TIMER4:
#if defined power_timer4_enable
      power_timer4_enable();
#endif
      break;
    case POWER_TIMER5:
#if defined power_timer5_enable
      power_timer5_enable();
#endif
      break;
    case POWER_SERIAL0:
#if defined power_usart0_enable
      power_usart0_enable();
#endif
      break;
    case POWER_SERIAL1:
#if defined power_usart1_enable
      power_usart1_enable();
#endif
      break;
    case POWER_SERIAL2:
#if defined power_usart2_enable
      power_usart2_enable();
#endif
      break;
    case POWER_SERIAL3:
#if defined power_usart3_enable
      power_usart3_enable();
#endif
      break;
    case POWER_USB:
#if defined power_usb_enable
      power_usb_enable();
#endif
      break;
    case POWER_ALL:
#if defined power_all_enable
      power_all_enable();
#endif
    default:
      break;
  }
}

static inline void disablePower(uint8_t) __attribute__((always_inline, unused));
static inline void disablePower(uint8_t P)
{
  switch(P)
  { 
    case POWER_ADC:
#if defined power_adc_disable
      power_adc_disable();
#endif
      break;
    case POWER_SPI:
#if defined power_spi_disable
      power_spi_disable();
#endif
      break;
    case POWER_WIRE:
#if defined power_twi_disable
      power_twi_disable();
#endif
      break;
    case POWER_TIMER0:
#if defined power_timer0_disable
      power_timer0_disable();
#endif
      break;
    case POWER_TIMER1:
#if defined power_timer1_disable
      power_timer1_disable();
#endif
      break;
    case POWER_TIMER2:
#if defined power_timer2_disable
      power_timer2_disable();
#endif
      break;
    case POWER_TIMER3:
#if defined power_timer3_disable
      power_timer3_disable();
#endif
      break;
    case POWER_TIMER4:
#if defined power_timer4_disable
      power_timer4_disable();
#endif
      break;
    case POWER_TIMER5:
#if defined power_timer5_disable
      power_timer5_disable();
#endif
      break;
    case POWER_SERIAL0:
#if defined power_usart0_disable
      power_usart0_disable();
#endif
      break;
    case POWER_SERIAL1:
#if defined power_usart1_disable
      power_usart1_disable();
#endif
      break;
    case POWER_SERIAL2:
#if defined power_usart2_disable
      power_usart2_disable();
#endif
      break;
    case POWER_SERIAL3:
#if defined power_usart3_disable
      power_usart3_disable();
#endif
      break;
    case POWER_USB:
#if defined power_usb_disable
      power_usb_disable();
#endif
      break;
    case POWER_ALL:
#if defined power_all_disable
      power_all_disable();
#endif
    default:
      break;
  }
}

#endif
// WPOWER_H
