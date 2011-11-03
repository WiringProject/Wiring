/**
 * Transmissive optical sensor without aperture Vishay TCST1000/TCST2000
 * by Diana Fernandez
 * 
 * Demonstrates how to use a transmisive optical sensor. This sensor is used in
 * mechanisms to detect when the gap in the top is blocked by an object.
 * When the sensor detects an interruption the Wiring onboard LED is turned on.
 */

int sensorSwitch = 9;  // digital pin to attach the switch
int sensorLED = 8;     // sensor LED
int boardLED = WLED;   // Wiring onboard LED

void setup()
{
  pinMode(sensorSwitch, INPUT);   // sets digital pin 1 as input
  pinMode(sensorLED, OUTPUT);     // sets digital pin 0 as output
  pinMode(boardLED, OUTPUT);      // sets on-board LED digital pin as output
  digitalWrite(sensorLED, HIGH);  // turns ON the sensor LED
}

void loop()
{
  // make the onboard LED to show the sensor status
  digitalWrite(boardLED, digitalRead(sensorSwitch));
}
