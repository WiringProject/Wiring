/**
 * Switching a 120-240VAC light bulb with a general purpose optocoupler and a TRIAC
 * Optocupler MOC3021, TRIAC BTA08-600C
 * by BARRAGAN http://barraganstudio.com
 * 
 * Optocouplers enable you to control one circuit from another circuit
 * with no electronic connection between the two circuits for example to control
 * a device (switching it ON or OFF) from the Wiring harware.
 * A TRIAC is an electronic switch capable of switching AC devices by applying
 * a small current at the Gate, making possible to control high AC voltages from
 * the Wiring hardware.
 * Internally the Optocupler has an LED that's why the connection and code
 * looks like the LED example, when the Wiring board sets the pin 8 to HIGH the
 * internal LED turns ON activating a an internal light sensor that enables the
 * flow of electricity between whatever is connected in the main terminal pins.
 * There are different types of optocouplers but the functioning is very similar
 * the MOC3021 is just one type and it is useful for using it with the TRIAC.
 * It is always very useful to consult the datasheet of the optocoupler you're
 * using for specific needs.
 */

int optocouplerPin = 8;  // Optocoupler anode (+) pin connected to digital pin 8

void setup()
{
  pinMode(optocouplerPin, OUTPUT);  // sets the digital pin as output
}

void loop()
{
  digitalWrite(optocouplerPin, HIGH);   // switch ON the triac
  delay(1000);                          // waits for a second
  digitalWrite(optocouplerPin, LOW);    // switch OFF the triac
  delay(1000);                          // waits for a second
}


