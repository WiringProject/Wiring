/**
 * Conditionals.
 * 
 * Conditions are like questions.
 * They allow a program to decide to take one action if
 * the answer to a question is true or to do another action
 * if the answer to the question is false.
 * The questions asked within a program are always logical
 * or relational statements. For example, if the variable 'i' is
 * equal to zero then turn on a light.
 */

int RED = 8;   // red LED on digital pin 8
int BLUE = 9;  // blue LED on digital pin 9

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  for (int i = 10; i < 32000; i += 10)
  {
    // If 'i' divides by 37 with no remainder turn ON the blue LED
    // else turn ON the red LED
    if (i % 37 == 0)
    {
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, HIGH);
      delay(200);  // delay to visualize the LED change
    }
    else
    {
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      delay(200);  // delay to visualize the LED change
    }
  }
}

