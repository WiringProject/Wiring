/**
 * Simple Serial communication
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to print data to the serial port. The data is
 * received by MaxMSP.
 * The MaxMSP patch is included below as text.
 * Copy the text of the patch open a new patch in MaxMSP and paste.
 */

byte value = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.write(value);
  value = value + 1;
  delay(100);
}

/* MaxMSP patch copy, go to Max open a new patch and paste

{
  "boxes" : [     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "number object to see the data coming from the board",
        "patching_rect" : [ 150.0, 367.0, 293.0, 20.0 ],
        "id" : "obj-21",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "number",
        "patching_rect" : [ 54.0, 366.0, 50.0, 20.0 ],
        "id" : "obj-20",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 2,
        "fontsize" : 12.0,
        "outlettype" : [ "int", "bang" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "toggle object to open/close the serial and start/stop the patch",
        "linecount" : 3,
        "patching_rect" : [ 97.0, 25.0, 150.0, 48.0 ],
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
        "patching_rect" : [ 54.0, 44.0, 20.0, 20.0 ],
        "id" : "obj-17",
        "numinlets" : 1,
        "numoutlets" : 1,
        "outlettype" : [ "int" ]
      }

    }
,     {
      "box" :       {
        "maxclass" : "comment",
        "text" : "select object with two options, to trigger messages, close and port ",
        "linecount" : 2,
        "patching_rect" : [ 220.0, 114.0, 227.0, 34.0 ],
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
        "patching_rect" : [ 147.0, 121.0, 62.0, 20.0 ],
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
        "text" : "Queue-based metronome",
        "patching_rect" : [ 127.0, 89.0, 150.0, 20.0 ],
        "id" : "obj-14",
        "fontname" : "Arial",
        "numinlets" : 1,
        "numoutlets" : 0,
        "fontsize" : 12.0
      }

    }
,     {
      "box" :       {
        "maxclass" : "newobj",
        "text" : "qmetro 10",
        "patching_rect" : [ 54.0, 102.0, 65.0, 20.0 ],
        "id" : "obj-13",
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
        "text" : "The serial object, port at 9600bps",
        "patching_rect" : [ 150.0, 324.0, 188.0, 20.0 ],
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
        "patching_rect" : [ 193.0, 269.0, 39.0, 18.0 ],
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
        "patching_rect" : [ 257.0, 185.0, 175.0, 89.0 ],
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
        "patching_rect" : [ 193.0, 187.0, 34.0, 18.0 ],
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
        "patching_rect" : [ 193.0, 222.0, 41.0, 18.0 ],
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
        "patching_rect" : [ 54.0, 325.0, 79.0, 20.0 ],
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
        "destination" : [ "obj-13", 0 ],
        "hidden" : 0,
        "midpoints" : [ 63.5, 82.5, 63.5, 82.5 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-17", 0 ],
        "destination" : [ "obj-15", 0 ],
        "hidden" : 0,
        "midpoints" : [ 63.5, 92.0, 156.5, 92.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 1 ],
        "destination" : [ "obj-7", 0 ],
        "hidden" : 0,
        "midpoints" : [ 178.0, 219.0, 202.5, 219.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-7", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [ 202.5, 255.0, 63.5, 255.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-10", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [ 202.5, 309.0, 63.5, 309.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-4", 0 ],
        "destination" : [ "obj-20", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-13", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [  ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-15", 0 ],
        "destination" : [ "obj-10", 0 ],
        "hidden" : 0,
        "midpoints" : [ 156.5, 255.0, 202.5, 255.0 ]
      }

    }
,     {
      "patchline" :       {
        "source" : [ "obj-8", 0 ],
        "destination" : [ "obj-4", 0 ],
        "hidden" : 0,
        "midpoints" : [ 202.5, 207.0, 63.5, 207.0 ]
      }

    }
 ]
}

*/
