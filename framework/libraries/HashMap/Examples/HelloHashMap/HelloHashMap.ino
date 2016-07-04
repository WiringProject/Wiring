#include <HashMap.h>

//define hashmap storage variable
HashMap<String, int> hashMap;

void setup(){
  
  Serial.begin(9600);
  
  //putting object into hashmap variable
  hashMap.put("name",18);
  hashMap.put("test",200);
  hashMap.put("qwer",1234);
  hashMap.put("abc",123);
  hashMap.put("AlphaBeta",20);
  
  //getting value
  Serial.println(hashMap.getValue("qwer")); //print 1234
  
  
  //containsKey function
  Serial.println(hashMap.containsKey("test")); //print 1
  
  Serial.println(hashMap.containsKey("ciaociao")); //print 0
  
 
  //length
  Serial.println(hashMap.length()); //print 5
  
  //remove
  hashMap.remove("abc"); //remove object that is associated to "abc" key
  
  Serial.println(hashMap.length()); //print 4
  
  
}

void loop(){/*nothing to loop*/}
