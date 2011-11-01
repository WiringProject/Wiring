/**
 * Timer
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to create a timer to print a message every 7 seconds
 */

unsigned long previousTime = 0;

void setup()
{
  Serial.begin(9600);
  previousTime = millis(); // mark the initial time
}

void loop()
{
  // if 7 seconds have passed since last mark
  if ((millis() - previousTime) >= 7000)
  {
    Serial.println("seven seconds have passed"); //print message
    previousTime = millis(); // mark again
  }
}
