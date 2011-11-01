/**
 * 74LS595 Shift Register
 * by BARRAGAN http://barraganstudio.com
 * 
 * Sends the value stored in the byte variable counter to the
 * shift register. The shift register outputs QA to QH will
 * reflect the value sent.
 */

int data = 8;      // Wiring pin 8 for data
int clock = 9;     // Wiring pin 9 for clock
int strobe = 10;   // Wiring pin 10 for the strobe (latch)
byte counter = 0;

void setup()
{
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(strobe, OUTPUT);
}

void loop()
{
  shiftOut(data, clock, LSBFIRST, counter);  // writes counter to the shift register
  digitalWrite(strobe, HIGH);
  delay(1);  // or even delayMicroseconds(50);
  digitalWrite(strobe, LOW);
  delay(1000);
  counter = counter + 1;
}

