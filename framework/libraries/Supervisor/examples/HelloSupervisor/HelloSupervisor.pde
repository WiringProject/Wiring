/** 
 * HelloSupervisor
 * by BREVIG http://alexanderbrevig.com
 * 
 * This example implements a rule that is:
 * 'keep the WLED on the first ten seconds of program execution'
 * You could define your own rules, for instance:
 * - turn on heat if temerature drops below x
 * - if the light is red, stop the car
 */

#include <Supervisor.h>

int x = 0;

/*
  Define the rule itself
*/
SupervisedRule<int> ledOnFirstTenSeconds(x,checkFirstTen,handleAfterTen);

/*
  Define the rule helpers
*/
//this function will return true the first ten seconds
//when it return false (aka the rule failed) the handler will be called
boolean checkFirstTen(int x) {
  if (millis()<10000) { return true; } return false;
}

//the first ten seconds have passed
//turn off the LED and remove the rule
void handleAfterTen(int &x) {
  digitalWrite(WLED, LOW);
  Supervisor.removeRule(ledOnFirstTenSeconds);
}

void setup()
{
  Supervisor.addRule(ledOnFirstTenSeconds);

  pinMode(WLED,OUTPUT);
  digitalWrite(WLED, HIGH);
}

void loop()
{
  Supervisor.checkRules();
} 
