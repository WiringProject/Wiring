/**
 * HelloHashMap
 * by BREVIG http://alexanderbrevig.com
 * 
 * Demonstrate the usage of a HashMap
 * This HashMap will pair a char* string to an integer and it has the capacity to hold three pairs
 */

#include <HashMap.h>

CreateHashMap(hashMap, char*, int, 3); //create hashMap that pairs char* to int and can hold 3 pairs

void setup()
{
  //add and store keys and values
  hashMap["newKey"] = 12;
  hashMap["otherKey"] = 13;
  
  //check if overflow (there should not be any danger yet)
  Serial.print("Will the hashMap overflow now [after 2 assigns] ?: ");
  Serial.println(hashMap.willOverflow());
  
  hashMap["lastKey"] = 14;
  
  //check if overflow (this should be true, as we have added 3 of 3 pairs)
  Serial.print("Will the hashMap overflow now [after 3 assigns] ?: ");
  Serial.println(hashMap.willOverflow());
  
  //it will overflow, but this won't affect the code.
  hashMap["test"] = 15;

  //change the value of newKey
  Serial.print("The old value of newKey: ");
  Serial.println(hashMap["newKey"]);
  
  hashMap["newKey"]++;
  
  Serial.print("The new value of newKey (after hashMap['newKey']++): ");
  Serial.println(hashMap["newKey"]);

  //remove a key from the hashMap
  hashMap.remove("otherKey");
  
  //this should work as there is now an availabel spot in the hashMap
  hashMap["test"] = 15;

  printHashMap();
}

void loop() {}

void printHashMap() 
{
  for (int i=0; i<hashMap.size(); i++) 
  {
    Serial.print("Key: ");
    Serial.print(hashMap.keyAt(i));
    Serial.print(" Value: ");
    Serial.println(hashMap.valueAt(i));
  }
}
