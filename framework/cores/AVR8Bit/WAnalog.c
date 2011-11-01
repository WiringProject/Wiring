/* $Id: WAnalog.c 1152 2011-06-06 21:50:10Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Analog input and output methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>

/*************************************************************
 * Globals
 *************************************************************/

uint8_t analog_reference = DEFAULT;
uint8_t adcFirstTime = true;


/*************************************************************
 * Analog Input
 *************************************************************/

void adcInit()
{
  // Set the ADC for single conversion, ck/128 prescalar, AREF = AVCC = 5V

  // Set ADC voltage reference to AVCC (REFS0 = 1, REFS1 = 0)
  ADMUX = (1 << REFS0);
  // Set ADC Control:
  // ADC Enabled, Prescalar = ck/128
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // ADCSRA = _BV(ADEN)|_BV(ADSC)|_BV(ADATE)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
  // ADCSRB &= ~(_BV(ADTS2)|_BV(ADTS1)|_BV(ADTS0));
}

void analogReference(uint8_t mode)
{
  // can't actually set the register here because the default setting
  // will connect AVCC and the AREF pin, which would cause a short if
  // there's something connected to AREF.
  analog_reference = mode;
}

int16_t analogRead(uint8_t pin)
{
#if defined(ADCSRA)
  uint8_t low, high;

  if (adcFirstTime == true)
  {
    adcInit();
    adcFirstTime = false;
  }

  // The only megaAVR 8 bit controllers that have 16 single-ended a/d channels
  // are the ATmega640/1280/2560
#if defined(MUX5)
  // the MUX5 bit of ADCSRB selects whether we're reading from channels
  // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif

  // set the analog reference (high two bits of ADMUX) and select the
  // single ended input channel (low 3 bits).

  ADMUX = (analog_reference << 6) | (pin & 0x07);

  // start the conversion
  ADCSRA |= (1 << ADSC);

  // ADSC is cleared when the conversion finishes
  while (ADCSRA & (1 << ADSC));

  // we have to read ADCL first; doing so locks both ADCL
  // and ADCH until ADCH is read.  reading ADCL second would
  // cause the results of each conversion to be discarded,
  // as ADCL and ADCH would be locked when it completed.
  low  = ADCL;
  high = ADCH;

  // combine the two bytes
  return (high << 8) | low;
#else
  // we dont have an ADC, return 0
  return 0;
#endif
}
