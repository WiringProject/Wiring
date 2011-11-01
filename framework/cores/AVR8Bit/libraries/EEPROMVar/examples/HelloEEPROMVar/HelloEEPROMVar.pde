/**
 * HelloEEPROMVar
 * by BREVIG http://alexanderbrevig.com
 *
 * A simple example that uses this library to store a variable that will be saved
 * and persist through power cycles.
 * Great for settings
 */

#include <EEPROM.h>
#include <EEPROMVar.h>

EEPROMVar<int> eepromRunCounts(1);
EEPROMVar<float> eepromPI(3.1415f);

void setup() 
{
  Serial.begin(115200);
  Serial.print("This program has been ran ");
  Serial.print(eepromRunCounts);
  if (eepromRunCounts==1) 
  {
    Serial.println(" time.");
  } 
  else 
  {
    Serial.println(" times.");
  }
  Serial.print("As it multiplies PI by two each execution, the current value is ");
  Serial.println(eepromPI);
  
  eepromRunCounts++;
  eepromPI *= 2;
}

void loop() {
  //nothing to loop
}