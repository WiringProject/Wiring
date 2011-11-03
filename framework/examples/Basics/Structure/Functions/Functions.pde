/**
 * Functions.
 * 
 * The trafficLight() turns ON the specified light and waits 2 seconds.
 * Each call to trafficLight() specifies the pin in which a color LED
 * is connected, turns OFF all colors and then turn ON the one specified
 */
int RED = 8;
int YELLOW = 9;
int GREEN = 10;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop()
{
  trafficLight(RED);
  trafficLight(YELLOW);
  trafficLight(GREEN);
}

void trafficLight(int color)
{
  // turn OFF all lights
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  // turn ON the one received
  digitalWrite(color, HIGH);
  delay(2000);
}
