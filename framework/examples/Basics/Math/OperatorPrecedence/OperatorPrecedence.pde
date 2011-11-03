/**
 * Operator Precedence
 * 
 * If you don't explicitly state the order in which
 * an expression is evaluated, they are evaluated based
 * on the operator precedence. For example, in the statement
 * "4+2*8", the 2 will first be multiplied by 8 and then the result will
 * be added to 4. This is because the "*" has a higher precedence
 * than the "+". To avoid ambiguity in reading the program,
 * it is recommended that is statement is written as "4+(2*8)".
 * The order of evaluation can be controlled through placement of
 * parenthesis in the code. A table of operator precedence follows below.
 *
 */

// The highest precedence is at the top of the list and
// the lowest is at the bottom.
// Multiplicative: * / %
// Additive: + -
// Relational: < > <= >=
// Equality: == !=
// Logical AND: &&
// Logical OR: ||
// Assignment: = += -= *= /= %=

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 200; i += 4)
  {
    // The 30 is added to 70 and then evaluated
    // if it is greater than the current value of "i"
    // For clarity, write as "if(i > (30 + 70)) {"
    if (i > 30 + 70)
    {
      Serial.print(i, DEC);
      Serial.print(" ");
    }
  }

  Serial.println();

  // The 2 is multiplied by the 8 and the result is added to the 5
  int result = 4 + 2 * 8;
  Serial.println(result, DEC);

  // The 2 is added to the 4 and the result is multiplied by the 8
  result = (4 + 2) * 8;
  Serial.println(result, DEC);

  for (int i = 0; i < 200; i += 2)
  {
    // The relational statements are evaluated
    // first, and then the logical AND statements and
    // finally the logical OR.
    if (i > 20 && i < 50 || i > 100 && i < 200 - 20)
    {
      Serial.print(i, DEC);
      Serial.print(" ");
    }
  }
}

void loop()
{

}
