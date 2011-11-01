/**
 * All Analog Inputs to MaxMSP
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to print data to the serial port. The data is
 * received by MaxMSP.
 * The MaxMSP patch is included below as text.
 * Copy the text of the patch open a new patch in MaxMSP and paste.
 */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(0), DEC);
  Serial.print(",");
  Serial.print(analogRead(1), DEC);
  Serial.print(",");
  Serial.print(analogRead(2), DEC);
  Serial.print(",");
  Serial.print(analogRead(3), DEC);
  Serial.print(",");
  Serial.print(analogRead(4), DEC);
  Serial.print(",");
  Serial.print(analogRead(5), DEC);
  Serial.print(",");
  Serial.print(analogRead(6), DEC);
  Serial.print(",");
  Serial.println(analogRead(7), DEC);
  delay(100);
}

/* MaxMSP patch copy, go to Max open a new patch and paste

{
  "boxes" : [     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "use the first 4 inputs to set the background color of the window",
        "linecount" : 2,
        "patching_rect" : [ 261.0, 536.0, 267.0, 34.0 ],
        "id" : "obj-45",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "All analog inputs from the board",
        "patching_rect" : [ 342.0, 446.0, 181.0, 20.0 ],
        "id" : "obj-44",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "ascii to symbol",
        "patching_rect" : [ 138.0, 412.0, 89.0, 20.0 ],
        "id" : "obj-43",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "integer to ascii",
        "patching_rect" : [ 138.0, 380.0, 89.0, 20.0 ],
        "id" : "obj-42",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "puts everything onto a list",
        "patching_rect" : [ 138.0, 347.0, 147.0, 20.0 ],
        "id" : "obj-41",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "collect character and bang when get the character 10 (we are getting 8 numbers separated by ',': A0,A1,A2,A3,A4,A5,A6,A7 and a return (character 10).",
        "linecount" : 2,
        "patching_rect" : [ 138.0, 305.0, 437.0, 34.0 ],
        "id" : "obj-26",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "/ 1023.",
        "patching_rect" : [ 202.0, 536.0, 47.0, 20.0 ],
        "id" : "obj-25",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "float" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "bgcolor 0 0 0 0",
        "patching_rect" : [ 25.0, 579.0, 87.0, 19.0 ],
        "id" : "obj-27",
        "fontname" : "Verdana",
        "numinlets" : 4,
        "numoutlets" : 0,
        "fontsize" : 10.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "/ 4",
        "patching_rect" : [ 143.0, 536.0, 32.5, 20.0 ],
        "id" : "obj-49",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "/ 4",
        "patching_rect" : [ 84.0, 536.0, 32.5, 20.0 ],
        "id" : "obj-48",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "/ 4",
        "patching_rect" : [ 25.0, 536.0, 32.5, 20.0 ],
        "id" : "obj-47",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 441.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-40",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 381.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-39",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 321.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-38",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 261.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-37",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 202.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-36",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 143.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-35",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 84.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-34",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 25.0, 497.0, 50.0, 20.0 ],
        "id" : "obj-33",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "unpack 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
        "patching_rect" : [ 25.0, 446.0, 208.0, 20.0 ],
        "id" : "obj-32",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 15,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int", "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "fromsymbol",
        "patching_rect" : [ 25.0, 412.0, 73.0, 20.0 ],
        "id" : "obj-31",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "itoa",
        "patching_rect" : [ 25.0, 380.0, 46.0, 20.0 ],
        "id" : "obj-30",
        "fontname" : "Arial",
        "numinlets" : 3,
        "numoutlets" : 1,
        "fontsize" : 12.0,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "zl group",
        "patching_rect" : [ 25.0, 347.0, 53.0, 20.0 ],
        "id" : "obj-29",
        "fontname" : "Arial",
        "numinlets" : 2,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "", "" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "Queue-based metronome",
        "patching_rect" : [ 138.0, 94.0, 150.0, 20.0 ],
        "id" : "obj-28",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "select 10 13",
        "patching_rect" : [ 25.0, 305.0, 75.0, 20.0 ],
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
        "maxclass" : "newobj",
        "text" : "qmetro 10",
        "patching_rect" : [ 25.0, 94.0, 65.0, 20.0 ],
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
        "patching_rect" : [ 110.0, 28.0, 150.0, 48.0 ],
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
        "patching_rect" : [ 25.0, 46.0, 20.0, 20.0 ],
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
        "patching_rect" : [ 227.0, 122.0, 227.0, 34.0 ],
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
        "patching_rect" : [ 139.0, 126.0, 62.0, 20.0 ],
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
        "patching_rect" : [ 138.0, 274.0, 188.0, 20.0 ],
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
        "patching_rect" : [ 168.0, 225.0, 39.0, 18.0 ],
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
        "patching_rect" : [ 227.0, 162.0, 175.0, 89.0 ],
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
        "patching_rect" : [ 168.0, 163.0, 34.0, 18.0 ],
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
        "patching_rect" : [ 168.0, 193.0, 41.0, 18.0 ],
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
        "patching_rect" : [ 25.0, 274.0, 79.0, 20.0 ],
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
        "source" : [ "obj-32", 0 ],
        "destination" : [ "obj-33", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 4 ],
        "destination" : [ "obj-35", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 6 ],
        "destination" : [ "obj-36", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 8 ],
        "destination" : [ "obj-37", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 10 ],
        "destination" : [ "obj-38", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 12 ],
        "destination" : [ "obj-39", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 14 ],
        "destination" : [ "obj-40", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-31", 0 ],
        "destination" : [ "obj-32", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-30", 0 ],
        "destination" : [ "obj-31", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-29", 0 ],
        "destination" : [ "obj-30", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-14", 0 ],
        "destination" : [ "obj-29", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-14", 2 ],
        "destination" : [ "obj-29", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-4", 0 ],
        "destination" : [ "obj-14", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-6", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-17", 0 ],
        "destination" : [ "obj-6", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-17", 0 ],
        "destination" : [ "obj-15", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 0 ],
        "destination" : [ "obj-10", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 1 ],
        "destination" : [ "obj-7", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-32", 2 ],
        "destination" : [ "obj-34", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-33", 0 ],
        "destination" : [ "obj-47", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-34", 0 ],
        "destination" : [ "obj-48", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-35", 0 ],
        "destination" : [ "obj-49", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-36", 0 ],
        "destination" : [ "obj-25", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-25", 0 ],
        "destination" : [ "obj-27", 3 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-47", 0 ],
        "destination" : [ "obj-27", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-48", 0 ],
        "destination" : [ "obj-27", 1 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-49", 0 ],
        "destination" : [ "obj-27", 2 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
 ]
}

*/
