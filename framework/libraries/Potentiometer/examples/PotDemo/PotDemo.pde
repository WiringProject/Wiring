/**
 * PotDemo
 * by BREVIG http://alexanderbrevig.com
 * 
 * Display the intuitive way of using potentiomters when using this Hardware Abstraction class
 */

#include <Potentiometer.h>

Potentiometer potentiometer = Potentiometer(2); //a Potentiometer at analog in 2

void setup()
{
  Serial.begin(9800);
  Serial.println("Potentiometer example");
  delay(2000);
}

void loop()
{
  Serial.print("potentiometer.getValue() ");
  Serial.println(potentiometer.getValue(),DEC);
  Serial.print("potentiometer.getSector() ");
  Serial.println(potentiometer.getSector(),DEC);
  Serial.println();
  delay(1000);
}
