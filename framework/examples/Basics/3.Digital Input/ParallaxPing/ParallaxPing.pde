/**
 * Parallax PING Sensor
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates use of the pulseIn command to read data from the
 * Parallax PING Sensor
 */

int signalPin = 8;     // sensor signal pin connected to wiring pin 0
long elapsedtime = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  elapsedtime = 0;
  pinMode(signalPin, OUTPUT);  // set signalPin as OUTPUT

  // Send 0-1-0 pulse to activate the sensor
  digitalWrite(signalPin, LOW);
  delayMicroseconds(2);
  digitalWrite(signalPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(signalPin, LOW);

  // Listen to pulse
  pinMode(signalPin, INPUT);               // set signalPin as INPUT
  elapsedtime = pulseIn(signalPin, HIGH);  // get the length of the pusle while it is HIGH

  // print value through Serial

  Serial.println(elapsedtime, DEC);
  delay(100);
}


