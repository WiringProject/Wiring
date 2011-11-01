/**
 * Smooth
 * 
 * Reads Any analog sensor, (photoresistor or potentiometer), connected
 * to analog pin 0 and calculate an average using an array to keep track
 * of last readings.
 */

#define numSamples 10     // the number of samples to keep track of

int samples[numSamples];  // the readings from the sensor
int index = 0;            // index of the current reading
int total = 0;            // the sum of all samples
int average = 0;          // to calculate the average of all samples

void setup()
{
  Serial.begin(9600);     // Open the serial at 9600
  // Initialize the array's elements to 0
  for (int i = 0; i < numSamples; i++)
  {
    samples[i] = 0;
  }
}

void loop()
{
  // Subtract the value in current position from the total
  total = total - samples[index];
  // Read from the sensor a new value and store it
  samples[index] = analogRead(0);
  // Add the new reading to the total
  total = total + samples[index];
  // advance to the next position in the array:
  index = index + 1;
  // if index is at the end of the array go back to position 0
  if (index >= numSamples)
  {
    index = 0;
  }
  // Calculate the average of all elements
  average = total / numSamples;
  // Print average to the serial monitor
  Serial.println(average, DEC);
}


