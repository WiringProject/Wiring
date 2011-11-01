/**
 * Variable Scope.
 * 
 * Variables may either have a global or local "scope".
 * For example, variables declared within either the
 * setup() or loop() functions may be only used in these
 * functions. Global variables, variables declared outside
 * of setup() and loop(), may be used anywhere within the program.
 * If a local variable is declared with the same name as a
 * global variable, the program will use the local variable to make
 * its calculations within the current scope. Variables may be localized
 * within classes, functions, and iterative statements.
 */

int a = 20;  // Create a global variable "a"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // print global variable "a"
  Serial.println(a, DEC);

  // Create a new variable "a" local to the for() statement
  for (int a = 50; a < 80; a += 2)
  {
    Serial.print(a, DEC);
    Serial.print(" ");
  }
  Serial.println();
  // Create a new variable "a" local to the loop() method
  int a = 100;
  // Print the new local variable "a"
  Serial.println(a, DEC);

  // Make a call to the custom function printAnother()
  printAnother();

  // Make a call to the custom function printYetAnother()
  printYetAnother();
}

void printAnother()
{
  // Create a new variable "a" local to this method
  int a = 185;
  // print the local variable "a"
  Serial.println(a, DEC);
}

void printYetAnother()
{
  // Because no new local variable "a" is set,
  // this print is using the original global
  // variable "a" which is set to the value 20.
  Serial.println(a, DEC);
}
