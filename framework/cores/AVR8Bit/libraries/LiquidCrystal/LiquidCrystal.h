/* $Id: LiquidCrystal.h 1214 2011-06-27 05:51:19Z bhagman $
||
|| @author         John Raines <raine001 at tc dot umn dot edu>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Liquid Crystal Display (LCD) Hardware Abstraction Library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef LIQUIDCRYSTAL_H
#define LIQUIDCRYSTAL_H

#include <stdint.h>
#include <Print.h>
#include <Wiring.h>
typedef void (*FuncPtr)(int8_t chip);

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
//#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
#define LCD_Right 0
#define LCD_Left 1

#define DELAYPERCHAR 320

class LiquidCrystal : public Print
{
  public:
    LiquidCrystal(uint8_t rs, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t en2,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);  //4x40 LCD w 2x HD44780 controller chips, 2 enable lines to select between them   4 data pins
    LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t en2,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, void (*userFunc)(int8_t chip));   //4x40 LCD w 2x HD44780 controller chips, 2 enable lines to select between them   4 data pins
    LiquidCrystal(uint8_t rs, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    LiquidCrystal(uint8_t rs, uint8_t enable,
                  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3 , void (*userFunc)(int8_t chip));  //just define user busy flag test for the 2 forms I want to promote; deprecate 8 pins and RW;

    void init(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t en2,
              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, void (*userFunc)(int8_t chip));

    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

    void clear();
    void home();

    void noDisplay();
    void display();
    void noBlink();
    void blink();
    void noCursor();
    void cursor();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();

    void createChar(uint8_t, uint8_t[]);
    void setCursor(uint8_t, uint8_t);
    void write(uint8_t);
    void command(uint8_t);
    void commandBoth(uint8_t);
    inline LiquidCrystal& operator()(uint8_t x, uint8_t y)
    {
      setCursor(x, y);  //use along w Streaming.h to support: lcd(col,line)<<"a="<<a;
      return *this;
    }
    uint8_t numlines;
    uint8_t numcols;
  protected:
    void send(uint8_t, uint8_t);
    void write4bits(uint8_t);
    void begin2(uint8_t cols, uint8_t rows, uint8_t charsize, uint8_t chip);
    inline void delayPerHome(void)
    {
      if ((_rw_pin == 255) && (userFunc == NULL)) delayMicroseconds(2900);
    }
    FuncPtr userFunc; //pointer to user written busy test
    uint8_t _rs_pin;  // LOW: command.  HIGH: character.
    uint8_t _rw_pin;  // LOW: write to LCD.  HIGH: read from LCD.
    uint8_t _enable_pin; // activated by a HIGH pulse.
    uint8_t _en2;   //4x40 LCD
    uint8_t _chip;    //4x40
    int8_t _scroll_count;
    int8_t _x, _y, _setCursFlag;
    uint8_t _direction;

    uint8_t _busyPin; // for reading the busy flag on the LCD synonmymous w last pin number specified to constructor
    uint8_t _data_pins[4];
    uint8_t _numcols;
    uint8_t _numlines;
    uint8_t row_offsets[4];

    uint8_t _displaycontrol;   //display on/off, cursor on/off, blink on/off
    uint8_t _displaymode;      //text direction
};

#endif
// LIQUIDCRYSTAL_H
