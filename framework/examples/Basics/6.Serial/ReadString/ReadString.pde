/**
 * Read a string
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to read a string from the serial port
 * It is important to use delimiters in the String to read
 * for example read data until a '\n' or a designated character is found
 * This example reads data from the serial and stores into a String variable
 * until an 'L' is found, 'L' will be used as a terminator for the string
 * for testing with the console Send. Change the 'L' for whatever delimitator
 * you might want to use in your strings.
 */


char val; // variable to receive data from the serial port
String data = "";

void setup()
{
  Serial.begin(9600); // start serial communication at 9600bps
}

void loop()
{
  if (Serial.available())  // if data is available to read
  {
    val = Serial.read(); // read it and store it in 'val'
    if (val != 'L')      // if not an 'L'
    {
      data += val;       // add it to the data string
    }
    else
    {
      // if 'L' was received (our designated termination char)
      Serial.println("string received: " + data); // print the stored string
      data = ""; // empty data for next string reading
    }
  }
}

