/**
 * Hall sensor
 * by Juan Guillermo (Coco) Gomez
 * 
 * A hall sensor is a magnetic field sensor, it can detect when a magnet is in the proximity.
 * This example turns on the Wiring board LED when a
 * magnet is near the Hall sensor
 */

int pinHall = 8;  // Pin for the Hall sensor

void setup()
{
  pinMode(WLED, OUTPUT);  // sets the digital pin as output
  pinMode(pinHall, INPUT);  // sets the digital pin as input
}

void loop()
{
  if (digitalRead(pinHall) == HIGH)  // If a magnet is near the Hall sensor
  {
    digitalWrite(WLED, HIGH);  // turns ON the LED
  }
  else
  {
    digitalWrite(WLED, LOW);   // turn OFF the LED
  }
}
