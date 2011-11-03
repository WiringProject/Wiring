/**
 * 4N35 General purpose optocoupler
 * by BARRAGAN http://barraganstudio.com
 * 
 * Optocouplers enable you to control one circuit from another circuit
 * with no electronic connection between the two circuitsfor example to control
 * a toy or device (switching it ON or OFF) from the Wiring hardware
 * without tempering with the toy circuit.
 * Just interrupt the line you want to control and attach both ends to the S1
 * and S2 signals.
 * Internally the Optocupler has an LED that's why the connection and code
 * looks like the LED example, when the Wiring board sets the pin 8 to HIGH the
 * internal LED turns ON activating a an internal light sensor that enables the
 * flow of electricity between whatever is connected to S1 and S2.
 * There are different types of optocouplers but the functioning is very similar
 * the 4N35 is just one type and it is useful for hacking toys running on
 * batteries or small power adapters etc.
 * It is always very useful to consult the datasheet of the optocoupler you're
 * using for specific needs.
 */

int optocouplerPin = 8;  // Optocoupler anode pin connected to digital pin 8

void setup()
{
  pinMode(optocouplerPin, OUTPUT);  // sets the digital pin as output
}

void loop()
{
  digitalWrite(optocouplerPin, HIGH);  // connects S1 with S2
  delay(1000);                         // waits for a second
  digitalWrite(optocouplerPin, LOW);   // disconnects S1 from S2
  delay(1000);                         // waits for a second
}


