#include <LiquidCrystal.h>
// Try to exercise everything in LiquidCrystal for test purposes--:  You should be able to modify the first 4 lines
// of code to test different options and swap LCD boards (with contrast potentiometers attached directly) by plugging them directly 
// into the row of digital sockets on the Mega opposite the USB socket. Be careful about current draw on the backlight pins!!
//Arduino can only power these if current draw is <= 40 mAmps  
uint8_t nRows = 4;      //number of rows on LCD
uint8_t nColumns =16;   //number of columns
uint8_t rw = 255;         //255 if rw is connected vs 47 (or 49 for the 24x2) in the examples below; it should be pulled to GND if not controlled by the interface.
LiquidCrystal lcd(49,47,45, 35,33,31,29);  //there are multiple versions of this commented below; paste 'em in
                                        //this is kind of interesting: the LIquidCrystal object is created and init/begin is run
                                        //out here before setup(); before the board has power on the Mega!!! We need another begin to really
                                        //start the board later.

//======for an LCD with a single HD44780 type chip and 16 pin interface (eg 16x2 20x2 16x4 20x4) 4 data pinshttp://healthriskappraisal.org/LiquidCrystal440.zip

//Alternate interfaces to test for 2x16,4x20,4x16:
//LiquidCrystal lcd(49,47,45, 35,33,31,29);              // rs,rw,en, 4 data pins remember to set rw = 255 above
//LiquidCrystal lcd(49,47,45, 43,41,39,37, 35,33,31,29); // rs,rw,en 8 data pins remember to set rw = 255 above
//LiquidCrystal lcd(49,45, 35,33,31,29);                 // rs,en, 4 data pins  remember to set rw = 47 above
//LiquidCrystal lcd(49,45, 43,41,39,37, 35,33,31,29);    // rs,en 8 data pins  remember to set rw = 47 above

//alternate interfaces to test for 4x40:
//LiquidCrystal lcd(48,47,46,52,  41,40,39,38); rs,rw,en1,en2,  4 data lines  set rw to 255 I don't see any way to eliminate rw and include en2 with fcn overloading.
//LiquidCrystal lcd(48,255,46,52,   41,40,39,38); rs,rw,en1,en2,  4 data lines  set rw to 47 but this trick should let me use a grounded RW and skip the checkLcdBusyFlag if I want.

// Connections this assumes we attached a potentiometer  across LCD pins 1,2 and 3 with a standard 16 pin straight interface
//            and then plugged the LCD into the distal row of digital pins on a Mega
//            with the LCD extending away from the mega board:
//  this frees up the PWM pins for other uses. 
// rs (LCD pin 4) to Arduino pin 49
// rw (LCD pin 5) to Arduino pin 47
// enable (LCD pin 6) to Arduino pin 45
// LCD pin 15 to Arduino pin 27
// LCD pins d4, d5, d6, d7 to Arduino pins 35,33,31,29
//Arduino pins 51,43,41,39,37,23 are unused and hard to get at--you could interpose something like a stackable header between
//    the used pins and the LCD; then you could access the unused pins

//=====for a 4x40 LCD with 2 HD44780 type chips and 17 pin interface in 2 rows of 9; the pins are not arranged for
//     use with a breadboard, although you could solder a female socket onto the LCD board and use wires inserted 
//     female sockets or (as I did) to solder in stackable headers so that you can use the breadboard but
//     also can plug it into the 2 rows of digital sockets on the Mega.
//   LCD     Mega    Signal
//    18            Gnd        Backlight draws 480 mAmps!
//    17            +5V           
//    16      (53)    not used
//    15      52      En2 -- enable the 2nd HD44780 chip which controls the bottom 2 rows of the display
//    14      51*     +5V
//    13      50*     Gnd
//    12      --      Contrast resistor to Gnd
//    11      48      RS
//    10      47*     RW  -- could be strapped to Gnd 
//     9      46      En1 -- enable the 1st HD44780 which controls the top 2 rows
//    5-8    42-45*   Data 0-3 not used in 4 bit modes
//    1-4    38-41    Data 4-7
//This mode for the 4x40 is not working now://LiquidCrystal lcd(48,47,46,52,  45,44,43,42, 41,40,39,38); // rs,rw,en1,en2,  8 data lines  remember to set rw =255
//=========================================
//alternate versions to test for 2x24:  I have not seen this one actually work.
//LiquidCrystal lcd(50,49,48, 47,46,45,44, 43,42,41,40); // rs,rw,en 8 data pins remember to set rw = 255 above
//LiquidCrystal lcd(50,49,48,  43,42,41,40);            // rs,rw,en 4 data pins remember to set rw = 255 above
//LiquidCrystal lcd(50,48, 47,46,45,44, 43,42,41,40);   // rs,en 8 data pins remember to set rw = 49 above  -- these interfaces generally have unreliable initialization
//LiquidCrystal lcd(50,48, 43,42,41,40);                // rs,en 4 data pins remember to set rw = 49 above  -- these interfaces generally have unreliable initialization

//====2x24 LCD also has a non standard pinout and pins are numbered in the opposite direction:
//     1      53       Gnd
//     2      52        +5V
//     3      --        Contrast
//     4      50        RS
//     5      49        RW
//     6      48        EN
//    7-10    44-47    Data 0-3 not used in 4 bit mode
//    11-14   40-43    Data 4-7
//    15      --      Backlight +5v 147 mAmps!
//    16      --      Backlight Gnd

byte BACKLIGHT, BACKLTGND, POWER5V, GNDMain;

void setup(void) {
	// set some digital pins to high and low to provide LCD with power and gnd:
	//             most of them: 2x16,4x20 4x16
    BACKLIGHT = 27;    // pin 27 will control the backlight  //before I solder pins in, I check current on the backlight
    BACKLTGND = 25;    // PIN 25 will be set LOW to provide a Gnd for the backlight
    POWER5V = 53;      // we will set this HIGH to provide power on pin 2 of the LCD
    GNDMain = 255;      // next to pin 53 (in the pin "55" position) is a GND--pin 1 of the LCD goes there 
	
	if ((nColumns == 40) && (nRows ==4)) {     //4x40
		BACKLIGHT = 255;    // Digital IO pins cannot control the backlight   for the 4x40 double HD44780 LCD  draws 480 mAmps !!
		BACKLTGND = 255;    //Arduino is limited to 40 mAmps
		POWER5V = 51;      // we will set this HIGH to provide power on pin 2 of the LCD
		GNDMain = 50; 
	}
	if ((nRows ==2) && (nColumns ==24) ) {  //2x24
		BACKLIGHT = 255;    //    the 2x24  draws 147 mAmps !!
		BACKLTGND = 255;    // 
		POWER5V = 53;      // we will set this HIGH to provide power on pin 2 of the LCD
		GNDMain = 52; 
	}
	
	pinMode(POWER5V, OUTPUT);          //We're using a digital out as a 5V power source for the LCD
	digitalWrite(POWER5V, HIGH);
	if (BACKLIGHT != 255) {
		pinMode(BACKLIGHT, OUTPUT);        //set 255 if you need to wire backlight to gnd bo high current draw
		digitalWrite(BACKLIGHT, HIGH);     // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
		pinMode(BACKLTGND, OUTPUT);        //We're using a digital out as a GND for the backlight
		digitalWrite(BACKLTGND,LOW);
	}
	if (GNDMain != 255) {
		pinMode (GNDMain, OUTPUT);
		digitalWrite(GNDMain, LOW);

	}
	if (rw != 255) {
		pinMode(rw,OUTPUT);
		digitalWrite(rw,LOW);
	}
        pinMode(13,OUTPUT);
	randomSeed(analogRead(0));      //read unconnected pin to seed random number generator

	lcd.begin(nColumns,nRows);     //this is absolutely needed with this arrangement on the Mega--power was not
                                       // applied to the LCD when it was initialized as lcd was instantiated above!!
}

void loop(void) {                     //this runs the LCD with the interface selected above through a fairly comprehensive series of tests
	lcd.clear();
	lcd.setCursor((nColumns>>1)-2,0);
	lcd.print( (int)nColumns);
	lcd.print(",");
	lcd.print( (int)nRows);
	delay(1000);

	//mark the corners
	lcd.setCursor(0,0);
	lcd.print('1');
	lcd.setCursor(nColumns-1,nRows-1);
	lcd.print('4');
	lcd.setCursor(nColumns-1,0);
	lcd.print('2');
	lcd.setCursor(0,nRows-1);
	lcd.print('3');
	lcd.setCursor((nColumns>>1)-3,0);
	//  lcd.print("corners ");
	delay(1000);
	lcd.setCursor((nColumns>>1)-3,0);
	lcd.print("  scroll ");
	uint8_t rand=random(150);
	lcd.setCursor((nColumns>>1)-3,1);
	lcd.print((int)rand);
	int i = 0;
	while (i < rand) {
		lcd.scrollDisplayLeft(); 
		i++;
		delay(100);
	}
	// now we repeat the corner code to be sure we fixed the behavior of setCursor after scroll
    delay(1000);
	//mark the corners
	lcd.setCursor(0,0);
	lcd.print('a');
	lcd.setCursor(nColumns-1,nRows-1);
	lcd.print('d');
	lcd.setCursor(nColumns-1,0);
	lcd.print('b');
	lcd.setCursor(0,nRows-1);
	lcd.print('c');
	lcd.setCursor((nColumns>>1)-3,0);
	lcd.print("corners ");
	delay(1000);
	
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print('1');
	lcd.setCursor(nColumns-1,nRows-1);
	lcd.print('4');
	lcd.setCursor(nColumns-1,0);
	lcd.print('3');
	lcd.setCursor(0,nRows-1);
	lcd.print('2');
	lcd.setCursor((nColumns>>1)-3,0);
	lcd.print("corners");
	delay(1000);
	lcd.setCursor((nColumns>>1)-3,1);
	lcd.print("  scroll ");
	rand = random(150);
	lcd.setCursor((nColumns>>1)-3,2);
	lcd.print((int) rand);
	i = 0;
	while (i < rand) {
		lcd.scrollDisplayRight(); 
		i++;
		delay(100);
	}
	// now we repeat the corner code to be sure we fixed the behavior of setCursor after scroll
    delay(1000);
	//mark the corners  -- all of these corner tests are good ways to find off by one errors!
	
	lcd.setCursor(nColumns-1,nRows-1);
	lcd.print('d');
	lcd.setCursor(nColumns-1,0);
	lcd.print('b');
	lcd.setCursor(0,nRows-1);
	lcd.print('c');
        lcd.setCursor(0,0);
	lcd.print('a');
	lcd.setCursor((nColumns>>1)-3,0);
	lcd.print("corners ");
	delay(1000);
	
	//Cursor  on/off
	lcd.clear();
	lcd.setCursor (0,0);
	lcd.print("Cursor off");
	lcd.noCursor();
	delay(1000);
	// Turn on the cursor:
	lcd.setCursor (0,0);
	lcd.print("Cursor on ");
	lcd.cursor();
	delay(1000);
	lcd.setCursor (0,nRows-1);
	lcd.print("Cursor off");
	lcd.noCursor();
	delay(1000);
	// Turn on the cursor:
	lcd.setCursor (0,nRows-1);
	lcd.print("Cursor on ");
	lcd.cursor();
	delay(1000);
	//==enumerate lines on the display 
	lcd.clear();
	i = 0;
	while (i < nRows) {  
		lcd.setCursor(nColumns-8,i);
		lcd.print("ROW ");
		lcd.print(i+1);
		i++;
	}
	delay(1000);
	//=====try println
	lcd.clear();
        lcd.setCursor(0,0);
	i = 0;
	while (i < nRows) {  
		lcd.print("Println:# ");
		lcd.println(i+1);
		i++;
	}
	delay(1000);
	
	//=====Line wrap demo:
	lcd.clear();
	lcd.setCursor(nColumns-4,0);
	lcd.print("LINEWRAP01234567890");
	delay(200);
	if (nRows>=2) {
		lcd.setCursor(nColumns-4,1);
		lcd.print("linewrap01234567890");
		delay(1000);
		
		if (nRows >=4) {
			lcd.setCursor(nColumns-4,3);
			lcd.print("linewrap01234567890");
			delay(200); 
		}
    }
	delay(1000);
	i = 0;
	while (i < 11) {
		lcd.scrollDisplayLeft(); 
		i++;
		delay(100);
	}
	
    delay(1000);
    lcd.home();
    int length = nRows * nColumns;
    lcd.setCursor(0,0);
    char text[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    text[length] = '\0';
	
    lcd.print(text);  //here we are printing the entire screen with one long string  lets you be sure that linewrap happens exactly as it should
    delay(2000);
   uint8_t a =0;
  if ((nColumns == 8) && (nRows == 2) ) a=1;  //This is a trick to make a 'crazy 8' 16x1 LCD work reasonably in a right to left language; I suppose it could be added to the library routine
                                              // as a conditional but  that seems like too much support. what happens is that we write the 2nd line first; when that fills with (8) characters
                                              // it wraps onto the first line. This means that lcd.print("abcdefghijklmno"); will print from right to left as you desire.
    lcd.clear();
    lcd.rightToLeft();
    lcd.setCursor(nColumns-1,a); //now we print it in right to left mode to test the same thing
    lcd.print (text);
    delay(3000);
    lcd.leftToRight();
    
    long startTime=millis();    //let's try to benchmark how fast we can go; this will give us an idea about speed of the various interfaces 4/8 bit and checking busy flag or not:
    uint8_t repetitions = 20;
    char blanks[]="                                                                                                                                                                                                                                                                                                                                                 ";
    blanks[length] = '\0';
    while (repetitions--) {  //fill every screen pixel with text, then fill every pixel with blanks and repeat.
      lcd.setCursor(0,0);
      lcd.print(text);
      lcd.setCursor(0,0);
      lcd.print(blanks);
    }
    long endTime = millis();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Benchmark took ");
    lcd.setCursor(0,1);
    lcd.print(endTime - startTime);
    lcd.print(" millisecs.");
    delay(5000);
    
    
	//======setCursor===
	// loop from ASCII 'a' to ASCII 'z':
	lcd.home();        
	int thisLetter = 'a';
    // loop over the rows:
    for (int thisRow = 0; thisRow < nRows; thisRow++) {
		// loop over the columns:
		for (int thisCol = 0; thisCol < nColumns; thisCol++) {
			// set the cursor position:
			lcd.setCursor(thisCol,thisRow);
			// print the letter:
			lcd.print(thisLetter, BYTE);
			thisLetter++;
			if (thisLetter > 'z') thisLetter = 'a';
			delay(100);
		}
    }
	
	
	//========Autoscroll:  -- my arch nemesis !
	lcd.clear();
	// set the cursor to (0,0):
	lcd.setCursor(0, 0);
	// print from 0 to 9:
	lcd.print("Autoscroll");
	for (char thisChar = '1'; thisChar < '9'; thisChar++) {
		lcd.print(thisChar);
		delay(100);
	}
	
	// set the cursor to (nColumns,1):
	lcd.setCursor(0,1);
        lcd.print("Autoscroll");
	// set the display to automatically scroll:
	lcd.autoscroll();
	
	
	// print from 0 to 9:
	for (int thisChar = 0; thisChar < 10; thisChar++) {
		lcd.print(thisChar);
		delay(100);
	}
	// turn off automatic scrolling
	lcd.noAutoscroll();
if (nRows>2) {
	//========Autoscroll:  -- my arch nemesis !

	// set the cursor to (0,0):
	lcd.setCursor(0, nRows-2);
	// print from 0 to 9:
	lcd.print("Autoscroll");
	for (char thisChar = '1'; thisChar < '9'; thisChar++) {
		lcd.print(thisChar);
		delay(100);
	}
	
	// set the cursor to (nColumns,1):
	lcd.setCursor(0,nRows-1);
        lcd.print("Autoscroll");
	// set the display to automatically scroll:
	lcd.autoscroll();
	
	
	// print from 0 to 9:
	for (int thisChar = 0; thisChar < 10; thisChar++) {
		lcd.print(thisChar);
		delay(200);
	}
	// turn off automatic scrolling
	lcd.noAutoscroll();
}	
	//====== Turn on the blinking cursor:
    lcd.clear();
    lcd.setCursor(0,nRows-1);
    lcd.print("Blinking Cursor");
    lcd.blink();
    delay(1000);
	// Turn off the blinking cursor:
    lcd.noBlink();
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("Blinking Cursor");
    lcd.blink();
    delay(1000);
	// Turn off the blinking cursor:
    lcd.noBlink();
    delay(1000);
	
	//=====Turn display on and off:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("turn display off");
    delay(1000);
    // Turn off the display:
    lcd.noDisplay();
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("Turn Display ON ");  //sent to the LCD while the display is turned off.
	// Turn on the display:
    lcd.display();
    delay(1000);
	
    lcd.clear();
    lcd.home();
    lcd.setCursor(0,0);
    lcd.print(" Shift under program control ");
    // scroll 27 positions (display length + string length) to the left:
    for (int positionCounter = 0; positionCounter < 27; positionCounter++) {
		// scroll one position left:
		lcd.scrollDisplayLeft(); 
		// wait a bit:
		delay(100);
	}
	
	// scroll 27 positions (display length + string length) to the right:
	for (int positionCounter = 0; positionCounter < 27; positionCounter++) {
		// scroll one position right:
		lcd.scrollDisplayRight(); 
		// wait a bit:
		delay(100);
	}
	delay(1500);
	//======Text direction
	lcd.clear();
	lcd.setCursor(0,0);
	int thisChar ='a';
	for (int i = 0;i!=30; i++) {
		// reverse directions at 'm':
		if (thisChar == 'm') {
			// go right for the next letter
			lcd.rightToLeft(); 
		}
		// reverse again at 's':
		if (thisChar == 's') {
			// go left for the next letter
			lcd.leftToRight(); 
		}
		// reset at 'z':
		if (thisChar > 'z') {
			// go to (0,0):
			lcd.home(); 
			// start again at 0
			thisChar = 'a';
		}
		// print the character
		lcd.print(thisChar, BYTE);
		
		delay(200);
		//increment the letter:
		thisChar++;
	}
	lcd.clear();
	
	//======define charset
	uint8_t bell[8] = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
	uint8_t note[8] = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
	uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
	uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
	uint8_t duck[8] = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
	uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
	uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
	uint8_t retarrow[8] = { 0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
	
	
	lcd.createChar(0, bell);
	lcd.createChar(1, note);
	lcd.createChar(2, clock);
	lcd.createChar(3, heart);
	lcd.createChar(4, duck);
	lcd.createChar(5, check);
	lcd.createChar(6, cross);
	lcd.createChar(7, retarrow);
	lcd.home();
	
	i = 0;
	lcd.clear();
	while (i<nRows) {
		lcd.setCursor(0,i);
		lcd.print("user:");
		for (int j=0; j<7; j++) {
			lcd.print(j, BYTE);
		}
		
		i++;
	}
	delay(2000);
	
	
}

