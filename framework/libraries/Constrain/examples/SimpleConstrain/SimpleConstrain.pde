/**
 * SimpleConstrain
 * by BREVIG http://alexanderbrevig.com
 * 
 * Display a way of making, and using constrained variables
 */

#include <Constrain.h>

Constrained<float> constrainedFloat( 0.2 , 0.0 , 1.0 );
Constrained<byte> constrainedByte( 2 , 0 , 10 );

void setup()
{
  Serial.begin(9800);
  Serial.println("We have two constrained variables. \n\tThe first is a float, constrained to be within [0,1].\n\tThe other is a byte that is constrained to be within [0,10]");
  Serial.println("Setting the variables to 0");
  //set/reset the variable
  constrainedByte = 0;
  constrainedFloat = 0;
  Serial.println("Trying to make the variables exceed the constraint");
  for(byte i=0; i<12; i++)
  {
    Serial.print((float)constrainedFloat); //access value
    Serial.print(" ");
    Serial.println((byte)constrainedByte,DEC);
    constrainedFloat += 0.1;
    constrainedByte++;
  }
  Serial.println("Trying to make the variables go below the constraint");
  for(byte i=0; i<12; i++)
  {
    Serial.print(constrainedFloat.value);
    Serial.print(" ");
    Serial.println(constrainedByte.value,DEC);
    constrainedFloat -= 0.1;
    constrainedByte--;
  }
}

void loop(){}

