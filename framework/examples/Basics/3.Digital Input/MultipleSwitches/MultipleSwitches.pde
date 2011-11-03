/**
 * Multiple switches
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates the use of digital pins and switches.
 * The pin used as input is connected to a switch
 */

int switchPin_0 = 8; // switch connected to pin 8
int switchPin_1 = 9; // switch connected to pin 9
int switchPin_2 = 10; // switch connected to pin 10
int switchPin_3 = 11; // switch connected to pin 11
int switchPin_4 = 12; // switch connected to pin 12

void setup()
{
  pinMode(switchPin_0, INPUT);  // sets digital pin 8 as input
  pinMode(switchPin_1, INPUT);  // sets digital pin 9 as input
  pinMode(switchPin_2, INPUT);  // sets digital pin 10 as input
  pinMode(switchPin_3, INPUT);  // sets digital pin 11 as input
  pinMode(switchPin_4, INPUT);  // sets digital pin 12 as input
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(switchPin_0) == HIGH) // if the switch is pressed
  {
    Serial.print("ON ");
  }
  else                                // if switch not pressed
  {
    Serial.print("OFF ");
  }
  if (digitalRead(switchPin_1) == HIGH) // if the switch is pressed
  {
    Serial.print("ON ");
  }
  else                                // if switch not pressed
  {
    Serial.print("OFF ");
  }
  if (digitalRead(switchPin_2) == HIGH) // if the switch is pressed
  {
    Serial.print("ON ");
  }
  else                                // if switch not pressed
  {
    Serial.print("OFF ");
  }
  if (digitalRead(switchPin_3) == HIGH) // if the switch is pressed
  {
    Serial.print("ON ");
  }
  else                                // if switch not pressed
  {
    Serial.print("OFF ");
  }
  if (digitalRead(switchPin_4) == HIGH) // if the switch is pressed
  {
    Serial.println("ON");
  }
  else                                // if switch not pressed
  {
    Serial.println("OFF");
  }
  delay(100);
}
