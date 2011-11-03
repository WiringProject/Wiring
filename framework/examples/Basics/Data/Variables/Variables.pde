/**
 * Variables.
 * 
 * Variables are used for storing values. In this example, changing
 * the values of variables 'a' and 'b' significantly change the light pattern.
 */

int a = 20;
int b = 50;
int c = a * 8;
int d = a * 9;
int e = b - a;
int f = b * 2;
int g = f + e;

void setup()
{
  pinMode(WLED, OUTPUT);
}

void loop()
{
  digitalWrite(WLED, HIGH);
  delay(a);
  digitalWrite(WLED, LOW);
  delay(b);
  digitalWrite(WLED, HIGH);
  delay(c);
  digitalWrite(WLED, LOW);
  delay(d);
  digitalWrite(WLED, HIGH);
  delay(e);
  digitalWrite(WLED, LOW);
  delay(f);
  digitalWrite(WLED, HIGH);
  delay(g);
}
