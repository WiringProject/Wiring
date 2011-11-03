/**
 * Random.
 * 
 * Each time the program is loaded the result is different.
 */

int num;

void setup()
{
  Serial.begin(9600);
  randomSeed(200);
}

void loop()
{
  num = random(255);  // generate a random number between 0 and 255
  Serial.println(num, DEC);
  delay(30);
}


