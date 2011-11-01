#include <SmoothInterpolate.h>

void setup() 
{
  Serial.begin(9600);
  
  float arr[2] = { 0.0, 1.0}; //from 0.0 to 1.0
  // you start with 2 values, and you have 21 steps 
  // between each value
  SmoothInterpolate < 2 , 21 > smoothInterpolate = arr; 
  smoothInterpolate.calculate(); //smooth interpolate
  
  float prev = 0;
  for (int i=0; i<smoothInterpolate.size(); i++) {
    float smoothed = smoothInterpolate[i]; //acces the third value (index 2)
    Serial.print("At ");
    Serial.print(i);
    Serial.print(" value =");
    Serial.print(smoothed);
    Serial.print("\tdelta = ");
    Serial.print(smoothed-prev);
    prev = smoothed;
  }
    
}

void loop() 
{

}
