/**
 * Serial Read and MaxMSP
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to read data from the serial port.
 * If the data received is an 'H', the light turns ON,
 * if it is an 'L', the light turns OFF.
 * The MaxMSP patch is included as comented text below.
 * Copy the text of the patch open a new patch in MaxMSP and paste.
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 */

int val; // variable to receive data from the serial port
int ledpin = WLED; // Wiring board LED

void setup()
{
  pinMode(ledpin, OUTPUT); // pin WLED (on-board LED) as OUTPUT
  Serial.begin(9600);      // start serial communication at 9600bps
}

void loop()
{
  if (Serial.available())         // if data is available to read
  {
    val = Serial.read();          // read it and store it in 'val'
    if (val == 'H')               // if 'H' was received
    {
      digitalWrite(ledpin, HIGH); // turn ON the LED
    }
    else if (val == 'L')
    {
      digitalWrite(ledpin, LOW);  // otherwise turn it OFF
    }
  }
  delay(100);                     // wait 100ms for next reading
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

/* MaxMSP patch copy, go to Max open a new patch and paste

{
  "boxes" : [     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "atoi function to convert the characters H or L to integer befor sending them",
        "patching_rect" : [ 209.0, 283.0, 405.0, 20.0 ],
        "id" : "obj-27",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "toggle to blink the LED every second",
        "linecount" : 3,
        "patching_rect" : [ 26.0, 12.0, 93.0, 48.0 ],
        "id" : "obj-26",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "toggle to send an H or an L to turn On or OFF the LED",
        "linecount" : 4,
        "patching_rect" : [ 147.0, 68.0, 93.0, 62.0 ],
        "id" : "obj-25",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "toggle",
        "patching_rect" : [ 113.0, 69.0, 20.0, 20.0 ],
        "id" : "obj-24",
        "numinlets" : 1,
        "numoutlets" : 1,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "atoi",
        "patching_rect" : [ 112.0, 290.0, 46.0, 20.0 ],
        "id" : "obj-23",
        "fontname" : "Arial",
        "numinlets" : 3,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "list" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "message",
        "text" : "H",
        "patching_rect" : [ 156.0, 252.0, 32.5, 18.0 ],
        "id" : "obj-22",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "message",
        "text" : "L",
        "patching_rect" : [ 112.0, 252.0, 32.5, 18.0 ],
        "id" : "obj-19",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "select 0 1",
        "patching_rect" : [ 113.0, 220.0, 62.0, 20.0 ],
        "id" : "obj-14",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 3,
        "fontsize" : 12.0,
        "outlettype" : [ "bang", "bang", "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "toggle",
        "patching_rect" : [ 26.0, 69.0, 20.0, 20.0 ],
        "id" : "obj-13",
        "numinlets" : 1,
        "numoutlets" : 1,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "toggle",
        "patching_rect" : [ 25.0, 139.0, 20.0, 20.0 ],
        "id" : "obj-12",
        "numinlets" : 1,
        "numoutlets" : 1,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "metro 1000",
        "patching_rect" : [ 25.0, 104.0, 71.0, 20.0 ],
        "id" : "obj-6",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "toggle object to open/close the serial and start/stop the patch",
        "linecount" : 3,
        "patching_rect" : [ 196.0, 12.0, 150.0, 48.0 ],
        "id" : "obj-18",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "toggle",
        "patching_rect" : [ 166.0, 28.0, 20.0, 20.0 ],
        "id" : "obj-17",
        "numinlets" : 1,
        "numoutlets" : 1,
        "outlettype" : [ "int" ],
        "bgcolor" : [ 1.0, 0.337255, 0.619608, 1.0 ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "select object with two options, to trigger messages, close and port ",
        "linecount" : 2,
        "patching_rect" : [ 315.0, 148.0, 227.0, 34.0 ],
        "id" : "obj-16",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "select 0 1",
        "patching_rect" : [ 222.0, 153.0, 62.0, 20.0 ],
        "id" : "obj-15",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 3,
        "fontsize" : 12.0,
        "outlettype" : [ "bang", "bang", "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "The serial object, port at 9600bps",
        "patching_rect" : [ 209.0, 354.0, 188.0, 20.0 ],
        "id" : "obj-11",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "message",
        "text" : "close",
        "patching_rect" : [ 251.0, 252.0, 39.0, 18.0 ],
        "id" : "obj-10",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "add some message boxes and type their names for the basic communication, \"print\" (will print a list of serial ports), \"port a\" (to open the serial port) and \"close\" to close the serial port",
        "linecount" : 6,
        "patching_rect" : [ 315.0, 190.0, 175.0, 89.0 ],
        "id" : "obj-9",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "message",
        "text" : "print",
        "patching_rect" : [ 251.0, 190.0, 34.0, 18.0 ],
        "id" : "obj-8",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "message",
        "text" : "port a",
        "patching_rect" : [ 251.0, 220.0, 41.0, 18.0 ],
        "id" : "obj-7",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "serial a 9600",
        "patching_rect" : [ 112.0, 354.0, 79.0, 20.0 ],
        "id" : "obj-4",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "" ]
      }

    }
 ],
  "lines" : [     {
      "patchline" :       {
        "source" : [ "obj-17", 0 ],
        "destination" : [ "obj-15", 0 ],
        "hidden" : 0,
        "midpoints" : [ 175.5, 63.0, 249.0, 63.0, 249.0, 147.0, 231.5, 147.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-23", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-19", 0 ],
        "destination" : [ "obj-23", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-22", 0 ],
        "destination" : [ "obj-23", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-14", 0 ],
        "destination" : [ "obj-19", 0 ],
        "hidden" : 0,
        "midpoints" : [ 122.5, 240.0, 121.5, 240.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-14", 1 ],
        "destination" : [ "obj-22", 0 ],
        "hidden" : 0,
        "midpoints" : [ 144.0, 249.0, 165.5, 249.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-24", 0 ],
        "destination" : [ "obj-14", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-12", 0 ],
        "destination" : [ "obj-14", 0 ],
        "hidden" : 0,
        "midpoints" : [ 34.5, 207.0, 122.5, 207.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-6", 0 ],
        "destination" : [ "obj-12", 0 ],
        "hidden" : 0,
        "midpoints" : [ 34.5, 126.0, 34.5, 126.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-13", 0 ],
        "destination" : [ "obj-6", 0 ],
        "hidden" : 0,
        "midpoints" : [ 35.5, 90.0, 34.5, 90.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-8", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-7", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-10", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 1 ],
        "destination" : [ "obj-7", 0 ],
        "hidden" : 0,
        "midpoints" : [ 253.0, 186.0, 246.0, 186.0, 246.0, 213.0, 260.5, 213.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 0 ],
        "destination" : [ "obj-10", 0 ],
        "hidden" : 0,
        "midpoints" : [ 231.5, 249.0, 260.5, 249.0 ]
      }

    }
 ]
}

*/
