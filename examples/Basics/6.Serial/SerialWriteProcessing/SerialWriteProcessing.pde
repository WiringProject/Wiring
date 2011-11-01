/**
 * Serial Output
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to send data using the serial port.
 * A computer running a Processing program receives the data from the
 * serial port and fills a rectangle according to the value received.
 */

int switchpin = 8;    // switch connected to pin 8

void setup()
{
  pinMode(switchpin, INPUT); // pin 0 as INPUT
  Serial.begin(9600); // start serial communication at 9600bps
}

void loop()
{
  if (digitalRead(switchpin) == HIGH) // if switch is ON
  {
    Serial.write(1); // send 1 to Processing
  }
  else
  {
    Serial.write(0); // otherwise send 0 to Processing
  }
  delay(100); // wait 100ms for next print
}

/* Processing code for this example

// switch serial
// by BARRAGAN <http://barraganstudio.com>

// Demonstrates how to read data from the Wiring board, in order
// to fill a rectangle on the screen using a lighter color when a switch
// connected to the Wiring I/O board is pressed, and fill it with darker
// color when the switch is released.

// created 13 May 2004
// revised 11 September 2010

import processing.serial.*;

Serial port;  // create serial port object
int val;      // variable to receive data from the serial port

void setup()
{
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

void draw()
{
  if( 0 < port.available() )  // if data is available to read
  {
    val = port.read();        // read it and store it in 'val'
  }

  background(#222222);        // clear background

  if( val == 0 )              // if 0 was received
  {
    fill(#666660);            // set fill color
  }else{
    fill(#CCCCC0);            // set fill to a different color
  }

  rect(50, 50, 100, 100);     // draw square
}

*/


