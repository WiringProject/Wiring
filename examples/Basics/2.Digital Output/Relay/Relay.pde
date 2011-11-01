/**
 * Switching a 125VAC light bulb with a general purpose Relay
 * Relay 5VDC
 * by BARRAGAN http://barraganstudio.com
 * 
 * Relays enable you to control one circuit from another circuit
 * with no electronic connection between the two circuits for example to control
 * a device (switching it ON or OFF) from the Wiring harware.
 * A Relay is an electric switch capable of switching AC devices by applying
 * a small current at it, making possible to control high AC voltages from
 * the Wiring hardware.
 * It is always very useful to consult the datasheet of the optocoupler you're
 * using for specific needs.
 */

int relayPin = 8;

void setup()
{
  pinMode(relayPin, OUTPUT);  // sets the digital pin as output
}

void loop()
{
  digitalWrite(relayPin, HIGH);   // switch ON the triac
  delay(1000);                    // waits for a second
  digitalWrite(relayPin, LOW);    // switch OFF the triac
  delay(1000);                    // waits for a second
}


