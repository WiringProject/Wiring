/**
 * Driving Servo from a graphical user interface
 * by BARRAGAN http://barraganstudio.com
 * 
 * Receives data from the serial from Processing
 * to position a servo motor
 */

#include <Servo.h>

Servo myservo;              // create servo object to control a servo

int data = 0;               // variable to read from the serial port

void setup()
{
  myservo.attach(8);        // attaches the servo on pin 8 to the servo object
  Serial.begin(9600);       // starts the serial Serial at 9600 bauds
}

void loop()
{
  if (Serial.available())   // if data is available to read
  {
    data = Serial.read();   // read it and store it in 'val'
  }
  myservo.write(data);      // sets the servo position according to value in val
  delay(15);                // waits for the servo to get there
}



/* Processing code for this example

// servo serial
// by BARRAGAN <http://barraganstudio.com>

// Write data to the serial according to the position of a marker
// controlled by the mouse to position a servo motor

// created 2 January 2006

import processing.serial.*;

Serial port;        // create serial port object
int val;            // variable to receive data from the serial port
float mx = 0.0;
boolean firstTime = true;

void setup()
{
  size(200, 200);
  noStroke();
  frameRate(10);

  // List all the available serial ports in the output pane.
  // You will need to choose the port that the Wiring board is
  // connected to from this list. The first port in the list is
  // port #0 and the third port in the list is port #2.
  println(Serial.list());

  // Open the port that the Wiring board is connected to (in this case #2)
  // Make sure to open the port at the same speed Wiring is using (9600bps)
  port = new Serial(this, Serial.list()[1], 9600);
}

void draw()
{
  // one time wait for 3 seconds before starting to send data to
  // the serial
  if(firstTime) {
    delay(3000);
    firstTime = false;
  }
  background(#222222);    // clear background
  fill(#555555);    // set fill color
  rect(40, height/2-15, 120, 25); // draw square

  float dif = mouseX - mx;
  if(abs(dif) > 1.0) {
    mx = mx + dif/4.0;
  }
  mx = constrain(mx, 50, 150-1);// keeps marker on the screen
  noStroke();
  fill(255);
  rect(50, height/2-5, 100, 5);
  fill(204, 102, 0);

  rect(mx-2, height/2-5, 4, 5);// draws the position marker
  int angle = (int)(mx-50)*180/100; // scales the maker value to one in the range 0-180
  //print(angle + " ");   // prints the current angle (debug)
  port.write(angle);    // writes the angle to the serial port
}

*/
