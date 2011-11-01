/**
 * Data from multiple sensors / Processing
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from four photoresistors connected to the
 * analog input pins 0-3. The values read from the sensors are proportional
 * to the amount of light that hits their surface.
 * The values read are printed comma separated through the serial to use them in
 * Processing
 */

int sensorValue1, sensorValue2, sensorValue3, sensorValue4;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensorValue1 = analogRead(0);  // read sensor in analog input 0
  sensorValue2 = analogRead(1);  // read sensor in analog input 1
  sensorValue3 = analogRead(2);  // read sensor in analog input 2
  sensorValue4 = analogRead(3);  // read sensor in analog input 3
  Serial.print(sensorValue1, DEC);  // print sensor 1
  Serial.print(",");                // print ','
  Serial.print(sensorValue2, DEC);  // print sensor 2
  Serial.print(",");                // print ','
  Serial.print(sensorValue3, DEC);  // print sensor 3
  Serial.print(",");                // print ','
  Serial.println(sensorValue4, DEC);  // print sensor 4 and newline (println)
  delay(200);   // wait 200ms for next reading
}

// cut the code below and paste it into Processing

/**
 * Data from multiple sensors / Processing
 * by BARRAGAN <http://barraganstudio.com>
 * based on Tom Igoe's example from Making Things Talk book
 *
 * read serial data until a linefeed character is found
 * data are values comma separated. Split the data and convert it
 * into numbers in an array for firther use.
*/

/*
import processing.serial.*;

Serial myPort;
int linefeed = 10;   // Linefeed in ASCII
int numSensors = 4;  // we will be expecting for reading data from four sensors
int sensors[];       // array to read the 4 values
int pSensors[];      // array to store the previuos reading, usefur for comparing
// actual reading with the last one

void setup() {
  size(200, 200);
  // List all the available serial ports in the output pane.
  // You will need to choose the port that the Wiring board is
  // connected to from this list. The first port in the list is
  // port #0 and the third port in the list is port #2.
  println(Serial.list());

  myPort = new Serial(this, Serial.list()[1], 9600);
  // read bytes into a buffer until you get a linefeed (ASCII 10):
  myPort.bufferUntil(linefeed);
}

void draw() {
  if((pSensors != null)&&(sensors != null)) {

    // if valid data arrays are not null
    // compare each sensor value with the previuos reading
    // to establish change

    for(int i=0; i < numSensors; i++) {
      float f = sensors[i] - pSensors[i];  // actual - previous value
      if(f > 0) {
        println("sensor "+i+" increased by "+f);  // value increased
      }
      if(f < 0) {
        println("sensor "+i+" decreased by "+f);  // value decreased
      }
    }

    // now do something with the values read sensors[0] .. sensors[3]

  }
}

void serialEvent(Serial myPort) {

  // read the serial buffer:
  String myString = myPort.readStringUntil(linefeed);

  // if you got any bytes other than the linefeed:
  if (myString != null) {

    myString = trim(myString);

    // split the string at the commas
    // and convert the sections into integers:

    pSensors = sensors;
    sensors = int(split(myString, ','));

    // print out the values you got:

    for (int sensorNum = 0; sensorNum < sensors.length; sensorNum++) {
      print("Sensor " + sensorNum + ": " + sensors[sensorNum] + "\t");
    }

    // add a linefeed after all the sensor values are printed:
    println();

  }
}

*/

