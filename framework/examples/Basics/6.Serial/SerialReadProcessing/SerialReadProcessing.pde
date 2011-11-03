/**
 * Serial Input
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to read data from the serial port.
 * If the data received is an 'H', the light turns ON,
 * if it is an 'L', the light turns OFF.
 * The data comes from a computer running a Processing program, it sends
 * an 'H' if the mouse is over a rectangle otherwise it sends an 'L'.
 */

int val;  // variable to receive data from the serial port

void setup()
{
  pinMode(WLED, OUTPUT); // on-board LED as OUTPUT
  Serial.begin(9600); // start serial communication at 9600bps
}

void loop()
{
  if (Serial.available())  // if data is available to read
  {
    val = Serial.read(); // read it and store it in 'val'
    if (val == 'H')      // if 'H' was received
    {
      digitalWrite(WLED, HIGH); // turn ON the LED
    }
    else if (val == 'L')
    {
      digitalWrite(WLED, LOW); // otherwise turn it OFF
    }
  }
  delay(100); // wait 100ms for next reading
}

/* Processing code for this example

 // mouseover serial
 // by BARRAGAN <http://barraganstudio.com>

 // Demonstrates how to send data to the Wiring I/O board, in order to
 // turn ON a light if the mouse is over a rectangle and turn it off
 // if the mouse is not.

 // created 13 May 2004
 // revised 6 November 2009

 import processing.serial.*;

 Serial port;
 boolean firstTime = true;

 void setup()
 {
 size(200, 200);
 noStroke();
 // List all the available serial ports in the output pane.
 // You will need to choose the port that the Wiring board is
 // connected to from this list. The first port in the list is
 // port #0 and the third port in the list is port #2.
 println(Serial.list());

 // Open the port that the Wiring board is connected to (in this case #1)
 // Make sure to open the port at the same speed Wiring is using (9600bps)
 port = new Serial(this, Serial.list()[1], 9600);
 }

 // function to test if mouse is over square
 boolean mouseOverRect()
 {
 return ((mouseX >= 50)&&(mouseX <= 150)&&(mouseY >= 50)&(mouseY <= 150));
 }

 void draw()
 {
 // Wait 3 seconds for the Wiring board to start
 if(firstTime) {
 delay(3000);
 firstTime = false;
 }

 background(#222222);
 if(mouseOverRect())      // if mouse is over square
 {
 fill(#BBBBB0);         // change color
 port.write('H');       // send an 'H' to indicate mouse is over square
 } else {
 fill(#666660);         // change color
 port.write('L');       // send an 'L' otherwise
 }
 rect(50, 50, 100, 100);  // draw square
 }

 */
