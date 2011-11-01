/* $Id: bhexppgm.h 1153 2011-06-07 00:51:12Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | Extended AVR PGM Space - expansion for Atmel AVR 8 bit controllers.
|| | Functions/macros to facilitate parts >64K words (128K bytes).
|| #
||
|| @example
|| | debugstr_P(GET_FAR_ADDRESS(PSTRU("Flash string in upper memory\r")));
|| | printf_P(GET_FAR_ADDRESS(PSTR("Another flash string\r")));
|| #
||
|| @license Please see License.txt for license information.
||
*/

#ifndef BH_EXPPGM_H
#define BH_EXPPGM_H

#include <avr/pgmspace.h>

#define PSTRU(s) (__extension__({static unsigned char __c[] PROGMEM = (s); &__c[0];}))

//#if defined(RAMPZ)
#if FLASHEND > 0xFFFF

// same as uint_farptr_t
typedef uint32_t uint_flashptr_t;

// Copyright (c) 2006, Carlos Lamas
#define GET_FAR_ADDRESS(var)                  \
({                                            \
	uint_farptr_t tmp;                          \
                                              \
	__asm__ __volatile__(                       \
                                              \
			"ldi	%A0, lo8(%1)"           "\n\t"    \
			"ldi	%B0, hi8(%1)"           "\n\t"    \
			"ldi	%C0, hh8(%1)"           "\n\t"    \
			"clr	%D0"                    "\n\t"    \
		:                                         \
			"=d" (tmp)                              \
		:                                         \
			"p"  (&(var))                           \
	);                                          \
	tmp;                                        \
})

#define P_read_byte(a)  pgm_read_byte_far(a)
#define P_read_dword(a) pgm_read_dword_far(a)

#else

// standard 16 bit pointer
typedef uint16_t uint_flashptr_t;

#define GET_FAR_ADDRESS(x) (uint_flashptr_t)(x)

#define P_read_byte(a)  pgm_read_byte_near(a)
#define P_read_dword(a) pgm_read_dword_near(a)
#endif

#endif
// BH_EXPPGM_H
