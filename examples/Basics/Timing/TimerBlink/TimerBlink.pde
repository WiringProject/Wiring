/**
 * Led blink using millis()
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to blink an LED at an interval rate using a timer
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 */

int status = LOW; // led status, initially LOW
unsigned long previousTime; // timer variable
int interval = 5000; // interval for blinking 5 seconds

void setup()
{
  pinMode(WLED, OUTPUT);
  previousTime = millis();  // mark the time
}

void loop()
{
  // if current time - previousTime is greater than 5 seconds
  // change the LED status
  if ((millis() - previousTime) > interval)
  {
    // invert the LED status
    if (status == LOW)
    {
      status = HIGH;
    }
    else
    {
      status = LOW;
    }
    digitalWrite(WLED, status);
    previousTime = millis(); // mark the time
  }
}

