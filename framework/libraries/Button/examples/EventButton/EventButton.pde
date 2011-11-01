/**
 * EventButton
 * by BREVIG http://alexanderbrevig.com
 * 
 * Use a button connected to digital pin 12.
 * Digital pin 12 is used as input and connected to a button
 * 
 * Whis example demonstates the event API for buttons
 */
 
#include <Button.h>

/*
  Wire like this:
  GND -----/ button ------ pin 12
*/
Button button = Button(12,BUTTON_PULLUP_INTERNAL);

/*
  Define the event handler first, this part of the sketch has a "life of it's own"
*/
void handleButtonPressEvents(Button &btn)
{
  Serial.println("press");
  digitalWrite(WLED,HIGH);
}

void handleButtonReleaseEvents(Button &btn)
{
  Serial.println("release");
  digitalWrite(WLED,LOW);
}

void handleButtonClickEvents(Button &btn) 
{
  Serial.println("click");
  digitalWrite(WLED, LOW);
  delay(200);
  digitalWrite(WLED, HIGH);
  delay(200);
  digitalWrite(WLED, LOW);
  delay(200);
}

void handleButtonHoldEvents(Button &btn) 
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

/*
  Do your regular setup stuff here
*/
void setup()
{
  Serial.begin(9800);
  pinMode(WLED,OUTPUT);
  
  button.pressHandler(handleButtonPressEvents);
  button.releaseHandler(handleButtonReleaseEvents);
  button.clickHandler(handleButtonClickEvents);
  button.holdHandler(handleButtonHoldEvents,1500);
}

void loop()
{
  button.isPressed(); //update internal state
  /*
    Feel free to do your own processing here. 
    The buttons will be handeled 'automagically' by the handler functions
  */
}