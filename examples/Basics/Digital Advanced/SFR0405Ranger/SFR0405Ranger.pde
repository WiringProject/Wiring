/**
 * SRF04/SRF05 Devantech Ultrasonic Ranger Finder
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates reading data from the
 * Devantech Utrasonic Rangers SFR04/SFR05
 */

int echoPin = 9;  // digital pin to receive echo pulse
int triggerPin = 8;  // digital pin to send trigger pulse
unsigned long distance = 0;

void setup()
{
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(triggerPin, HIGH); // set HIGH for 15us to trigger ranging
  delayMicroseconds(15);
  digitalWrite(triggerPin, LOW);  // set pin LOW
  distance = pulseIn(echoPin, HIGH);  // read in pulse length
  distance = distance / 58; // calculate distance from pulse length
  Serial.println(distance, DEC);
  delay(50);  // wait 50ms for next ranging
}

