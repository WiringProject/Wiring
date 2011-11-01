/*
NewSoftSerial.h - Multi-instance software serial library

-- Interrupt-driven receive and other improvements by ladyada
-- Tuning, circular buffer, derivation from class Print,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart
-- Stream.h support by Brett Hagman (http://www.roguerobotics.com/)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)
-- ATmega644P support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/

#ifndef NewSoftSerial_h
#define NewSoftSerial_h

#include <inttypes.h>
#include <Stream.h>

/******************************************************************************
* Definitions
******************************************************************************/

#define _NewSS_MAX_RX_BUFF 64 // RX buffer size
#define _NewSS_VERSION 10 // software version of this library
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class NewSoftSerial : public Stream
{
private:
  // per object data
  uint8_t _receivePin;
  uint8_t _receiveBitMask;
  volatile uint8_t *_receivePortRegister;
  uint8_t _transmitBitMask;
  volatile uint8_t *_transmitPortRegister;

  uint16_t _rx_delay_centering;
  uint16_t _rx_delay_intrabit;
  uint16_t _rx_delay_stopbit;
  uint16_t _tx_delay;

  uint16_t _buffer_overflow:1;
  uint16_t _inverse_logic:1;

  // static data
  static char _receive_buffer[_NewSS_MAX_RX_BUFF]; 
  static volatile uint8_t _receive_buffer_tail;
  static volatile uint8_t _receive_buffer_head;
  static NewSoftSerial *active_object;

  // private methods
  void recv();
  bool activate();
  virtual void write(uint8_t byte);
  uint8_t rx_pin_read();
  void tx_pin_write(uint8_t pin_state);
  void setTX(uint8_t transmitPin);
  void setRX(uint8_t receivePin);

  // private static method for timing
  static inline void tunedDelay(uint16_t delay);

public:
  // public methods
  NewSoftSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
  ~NewSoftSerial();
  void begin(long speed);
  void end();
  int read();
  int available(void);
  bool active() { return this == active_object; }
  bool overflow() { bool ret = _buffer_overflow; _buffer_overflow = false; return ret; }
  static int library_version() { return _NewSS_VERSION; }
  static void enable_timer0(bool enable);
  void flush();
  int peek();

  // public only for easy access by interrupt handlers
  static inline void handle_interrupt();
};


#endif
