/**
 * Light sensor / Processing
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a photoresistor connected to the analog input pin 0.
 * The value read from the sensor is proportional
 * to the amount of light that hits the sensor surface.
 * The value read is printed to the serial to use it in
 * Processing to control the color of a square
 */

int sensorValue;
int inputPin = 0;      // photoresistor pin

void setup()
{
  Serial.begin(9600);  // Start serial communication at 9600 bps
}

void loop()
{
  // Read the analog input pin, and set the value in the range 0-255
  // dividing by 4
  sensorValue = analogRead(inputPin) / 4;
  Serial.write(sensorValue);  // Send the value
  delay(100);  // Wait 100ms for next reading
}



/* Processing code for this example
 *
 * Light sensor / Processing
 * by BARRAGAN <http://barraganstudio.com>
 *
 * Read data from the serial port and assign it to a variable. Set the fill a
 * rectangle on the screen using the value read from a light sensor connected
 * to the Wiring board
 */

/*

import processing.serial.*;

Serial port;  // Create object from Serial class
int sensorValue;  // Data received from the serial port

void setup() {
  size(200, 200);
  noStroke();
  // List all the available serial ports in the output pane.
  // You will need to choose the port that the Wiring board is
  // connected to from this list. The first port in the list is
  // port #0 and the third port in the list is port #2.
  println(Serial.list());

  // Open the port that the Wiring board is connected to (in this case #2)
  // Make sure to open the port at the same speed Wiring is using (9600bps)
  port = new Serial(this, Serial.list()[2], 9600);
}

void draw() {
  if (0 < port.available()) {   // If data is available to read,
    sensorValue = port.read();  // read it and store it in val
  }
  background(204);              // Clear background
  fill(sensorValue);                    // Set fill color with the value read
  rect(50, 50, 100, 100);       // Draw square
}

*/
