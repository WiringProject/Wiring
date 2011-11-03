/**
 * RFID reading
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to read data from a Parallax RFID reader
 * connected to the Serial1 serial port and print the tag number
 * through the Serial serial port.
 */

byte val;
char code[10];
int bytesread = 0;

void setup()
{
  Serial1.begin(2400);  // RFID reader SOUT pin connected to Serial1 RX pin at 2400bps
  Serial.begin(9600);   // Serial set to 9600
  pinMode(4, OUTPUT);   // Set digital pin 4 as OUTPUT to connect it to the RFID /ENABLE pin
}

void loop()
{
  digitalWrite(4, LOW);                  // Activate the RFID reader
  if (Serial1.available() > 0)           // if data available from reader
  {
    if ((val = Serial1.read()) == 10)    // check for header
    {
      bytesread = 0;
      while (bytesread < 10)             // read 10 digit code
      {
        if (Serial1.available() > 0)
        {
          val = Serial1.read();
          if ((val == 10) || (val == 13)) // if header or stop bytes before the 10 digit reading
          {
            break;                       // stop reading
          }
          code[bytesread] = val;         // add the digit
          bytesread++;                   // ready to read next digit
        }
      }
      if (bytesread == 10)               // if 10 digit read is complete
      {
        Serial.print("TAG code is: ");   // possibly a good TAG
        Serial.println(code);            // print the TAG code
      }
      bytesread = 0;
      digitalWrite(4, HIGH);             // deactivate RFID reader
      delay(1000);                       // wait for a second
    }
  }
}


