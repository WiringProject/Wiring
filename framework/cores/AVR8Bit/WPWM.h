/* $Id: WPWM.h 1161 2011-06-08 02:44:34Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | PWM output methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WPWM_H
#define WPWM_H

// Prototypes

void pwmWrite(uint8_t pin, uint16_t val, uint8_t outputMode = 0b10);
inline void analogWrite(uint8_t pin, uint16_t val) { pwmWrite(pin, val); };
inline void pwmOff(uint8_t pin) { pwmWrite(pin, 0, 0); };
inline void noAnalogWrite(uint8_t pin) { pwmWrite(pin, 0, 0); };
void setPWMResolution(uint8_t pin, uint8_t bitResolution);
void setPWMPrescale(uint8_t pin, uint8_t prescalar);


#endif
// WPWM_H
