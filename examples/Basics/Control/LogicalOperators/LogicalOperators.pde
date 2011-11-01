/**
 * Logical Operators.
 * 
 * The logical operators for AND (&&) and OR (||) are used to
 * combine simple relational statements into more complex expressions.
 * The NOT (!) operator is used to negate a boolean statement.
 */

int RED = 8;  // red LED on digital pin 8
int BLUE = 9;  // blue LED on digital pin 9
boolean op = false;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  for (int i = 5; i <= 195; i += 5)
  {
    // Logical AND
    if ((i > 35) && (i < 100))
    {
      op = false;
    }

    // Logical OR
    if ((i <= 35) || (i >= 100))
    {
      op = true;
    }

    // Testing if a boolean value is "true"
    // The expression "if(op)" is equivalent to "if(op == true)"
    if (op)
    {
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, HIGH);
      delay(200);  // delay to visualize the LED change
    }

    // Testing if a boolean value is "false"
    // The expression "if(!op)" is equivalent to "if(op == false)"
    if (!op)
    {
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      delay(200);  // delay to visualize the LED change
    }
  }
}


