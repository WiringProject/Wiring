/**
 * PollingComplexButton
 * by BREVIG http://alexanderbrevig.com
 * 
 * Use a button connected to digital pin 12.
 * Digital pin 12 is used as input and connected to a button
 * 
 * This is similar to EventButton example, but it uses polling technique
 */
 
#include <Button.h>

/*
  Wire like this:
  GND -----/ button ------ pin 12
*/
Button button = Button(12,BUTTON_PULLUP_INTERNAL);

/*
  Do your regular setup stuff here
*/
void setup()
{
  Serial.begin(9800);
  pinMode(WLED,OUTPUT);
}

void loop()
{
  button.isPressed();
  if (button.stateChanged())
  {
    if (button.wasPressed()) 
    {
      handleButtonPressEvent();
    }
    else 
    {
      handleButtonReleaseEvent();
      handleButtonClickEvent();
    }
  }
  if (button.held(1500))
  {
    handleButtonHoldEvent();
  }
}


void handleButtonPressEvent()
{
  Serial.println("press");
  digitalWrite(WLED,HIGH);
}

void handleButtonReleaseEvent()
{
  Serial.println("release");
  digitalWrite(WLED,LOW);
}

void handleButtonClickEvent() 
{
  Serial.println("click");
  digitalWrite(WLED, LOW);
  delay(200);
  digitalWrite(WLED, HIGH);
  delay(200);
  digitalWrite(WLED, LOW);
  delay(200);
}

void handleButtonHoldEvent() 
{
  Serial.println("hold");
  for (int i=0; i<10; i++)
  {
    digitalWrite(WLED, HIGH);
    delay(20);
    digitalWrite(WLED, LOW);
    delay(20);
  }
  digitalWrite(WLED, HIGH);
}