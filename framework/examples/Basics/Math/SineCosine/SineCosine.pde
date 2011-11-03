/**
 * Sine Cosine.
 * 
 * sin() and cos().
 * Numbers between 0 and PI*2 (TWO_PI which is roughly 6.28)
 * are put into these functions and numbers between -1 and 1 are
 * returned.
 */


void setup()
{
  Serial.begin(9600);
  Serial.println("angle / cos(angle) / sin(angle)");
  for (int angle = 0; angle <= 90; angle += 5)
  {
    float c = cos(radians(angle));
    float s = sin(radians(angle));
    Serial.print(angle);
    Serial.print(" / ");
    Serial.print(c);
    Serial.print(" / ");
    Serial.println(s);
  }
}

void loop()
{

}

