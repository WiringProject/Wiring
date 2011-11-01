/** 
 * EEPROM store data
 * by BARRAGAN <http://barraganstudio.com>
 * 
 * Demostrates how to store data in the EEPROM
 */

#include <EEPROM.h> 

char val; 

void setup() { 
  if(EEPROM.read(5) != 'H') {  // If an H hassn't been stored before 
    // in the EEPROM address 5 
    EEPROM.write(5, 'H');  // store an 'H' in EEPROM address 5 
  }  
  val = EEPROM.read(5);    // read value stored in EEPROM address 5 

    pinMode(WLED, OUTPUT); 
} 

void loop() { 
  if( val == 'H' )  // if val is 'H' then turon ON the onboard LED (pin 48) 
  { 
    digitalWrite(WLED, HIGH); 
  } 
  delay(100); 
} 

