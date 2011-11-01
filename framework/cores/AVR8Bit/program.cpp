#include <Wiring.h>

float x = 0;
float y = 0;
char c = 'A';
int d; 

void setup()
{
  pinMode(48, OUTPUT);
}

void loop()
{
  x = 20 * sin(0.2);   
  y = 20 * cos(0.1);  
  d = toLowerCase(c); 
  digitalWrite(48, HIGH);
  delay(500);
  digitalWrite(48, LOW);
  delay(500);

}

