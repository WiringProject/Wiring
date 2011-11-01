/**
 * HelloPassword
 * by BREVIG http://alexanderbrevig.com
 * 
 * A demonstration of the Password library
 */

#include <Password.h>

Password password = Password( "1234" );

void setup(){
  Serial.begin(9600);
 
  password.append('1');   //add 1 to the guessed password
  password.append('2');   //add 2 to the guessed password
  password << '3' << '4'; //add 3 and 4 to the guessed password
  Serial.println( password.evaluate() ? "true":"false" ); //should print true, since 1234 == 1234
  
  password.reset(); //reset the guessed password to NULL
  Serial.println( password.evaluate() ? "true":"false" ); //should print false, since 1234 != NULL
  
  password.set("qwerty"); //set target password to qwerty
  Serial.println( password.is("qwerty") ? "true":"false" ); //should print true, since qwerty == qwerty
  Serial.println( password == "qwirty" ? "true":"false" ); //should print false, since qwerty != qwirty
}

void loop(){/*nothing to loop*/}
