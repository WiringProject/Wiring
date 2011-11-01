/**
 * Switchng a 12V lamp with an International Rectifiers IRLD024 Mosfet Switch
 * by BARRAGAN http://barraganstudio.com
 * 
 * A Mosfet is s special kind of transistor switch used to handle higher loads
 * than the Wiring board can handle by itself. Logic-level MOSFETs can be
 * connected directly to a digital output pin.
 * In this example the Wiring board is blinking a 12V lamp by using an IRLD024
 * Mosfet connected to the digital Pin 8
 * Don't forget to tie together the Wiring GND and the Lamp 12V power
 * supply GND.
 */

int mosfetPin = 8;  // Mosfet Gate pin connected to the Wiring I/O board pin 8

void setup()
{
  pinMode(mosfetPin, OUTPUT);  // sets the digital pin as output
}

void loop()
{
  digitalWrite(mosfetPin, HIGH);  // sets the Lamp on
  delay(1000);                    // waits for a second
  digitalWrite(mosfetPin, LOW);   // sets the Lamp off
  delay(1000);                    // waits for a second
}

