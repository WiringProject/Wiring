/**
 * Advanced Input, sparkfun usb weather board.
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to read data from the sparkfun usb weather board using the
 * Serial library. The weather board includes temperature, humidity and
 * barometric pressure.
 * The weather board is connected to the Serial1 serial port.
 */

String weatherSentence = "";  // string to read data from the weather board
int ready = 0;                // used to mark when we have a complete string to process
char data;                    // use to read a byte from the serial
char charArray[100];          // create a char 100 position char array por parsing the data

unsigned long humidity = 0, fahrenheit = 0, celcius = 0, SCPfahrenheit = 0, presure = 0;

void setup()
{
  Serial1.begin(9600);   // starts the second hardware serial port at 9600 to communicate with the weather board
  Serial.begin(9600);    // starts the serial at 9600
  pinMode(WLED, OUTPUT); // turn ON the board LED for diagnostics
  digitalWrite(WLED, HIGH);
}

void loop()
{
  while (Serial1.available() > 0)  // if data vailable from the weather board
  {
    data = Serial1.read();         // read it
    if ((data != '\n'))            // if no end of line
    {
      weatherSentence += data;     // add it to the string
    }
    else    // if end of line reached, readu to parse the buffer
    {
      ready = 1;
      break;
    }
  }
  if (ready == 1)  // parse the buffer
  {
    if (weatherSentence.startsWith("#"))  // verify if it is a good reading
    {
      // uncomment just to see what we got
      // Serial.println(buffer);
      weatherSentence.toCharArray(charArray, 100); // get the characters copied into charArray of size 100
      processReading(charArray); // parse the char array extracting the data
    }
    weatherSentence = ""; // clean up the string for next reading
    ready = 0;
  }
}

// function that parses information received in a char array
void processReading(const char packet[])
{
  byte i;
  char* endptr;

  // start parsing
  i = 0;
  i++;
  humidity = strtod(&packet[i], &endptr);  // next field: humidity

  while (packet[i++] != ',');      // next field: fahrenheit
  fahrenheit = strtod(&packet[i], &endptr);

  while (packet[i++] != ',');      // next field: celcius
  celcius = strtod(&packet[i], &endptr);

  while (packet[i++] != ',');      // next field: SCPfahrenheit
  SCPfahrenheit = strtod(&packet[i], &endptr);

  while (packet[i++] != ',');            // next field: presure
  presure = strtod(&packet[i], &endptr);

  while (packet[i++] != ',');      // next field: counter

  while (packet[i++] != '$');      // next field: checksum

  Serial.print("humidity: ");
  Serial.print(humidity, DEC);
  Serial.print(" fahrenheit: ");
  Serial.print(fahrenheit, DEC);
  Serial.print(" celcius: ");
  Serial.print(celcius, DEC);
  Serial.print(" SCPfahrenheit: ");
  Serial.print(SCPfahrenheit, DEC);
  Serial.print(" presure: ");
  Serial.println(presure, DEC);
}

