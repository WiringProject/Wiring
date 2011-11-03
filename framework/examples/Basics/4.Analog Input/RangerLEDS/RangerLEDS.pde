/**
 * Light Equalizer
 * by Ana Lucia Martinez Arias
 * 
 * Demonstrates how to connect and use a SHARP GP2D12 or GP2D120 infrared ranger sensor.
 * Interprets distance from the ranger sensor value
 * turning ON a number of LEDs accordingly.
 * The LEDs are connected to digital pins 0 to 9
 */

int distance = 0;

void turn_all_off()    // function to turn off all the lights
{
  for (int i = 6; i < 16; i++) //LEDs connected to digital pins 0-9
  {
    digitalWrite(i, LOW);
  }
}

void setup()
{
  Serial.begin(9600); // set the serial port to 9600
  for (int i = 6; i < 16; i++)
  {
    pinMode(i, OUTPUT);  // set pins 0-9 as outputs
  }
}

void loop()
{
  turn_all_off();                 // turns all lights off
  distance = analogRead(0);       // sensor connected to analog pin 0
  Serial.println(distance, DEC);  // prints the value read from the sensor

  if (distance > 50)
  {
    digitalWrite(6, HIGH);   // sets the current light on
  }

  if (distance > 100)
  {
    digitalWrite(7, HIGH);   // sets the current light on
  }

  if (distance > 150)
  {
    digitalWrite(8, HIGH);   // sets the current light on
  }

  if (distance > 200)
  {
    digitalWrite(9, HIGH);   // sets the current light on
  }

  if (distance > 250)
  {
    digitalWrite(10, HIGH);   // sets the current light on
  }

  if (distance > 300)
  {
    digitalWrite(11, HIGH);   // sets the current light on
  }

  if (distance > 350)
  {
    digitalWrite(12, HIGH);   // sets the current light on
  }

  if (distance > 400)
  {
    digitalWrite(13, HIGH);   // sets the current light on
  }

  if (distance > 450)
  {
    digitalWrite(14, HIGH);   // sets the current light on
  }

  if (distance > 500)
  {
    digitalWrite(15, HIGH);   // sets the current light on
  }

  delay(50);
}

