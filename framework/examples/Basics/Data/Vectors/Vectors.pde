/**
 * Vectors.
 * 
 * A vector is a growable array of elements. Like an array,
 * it contains components that can be accessed using an integer
 * index. However, the size of a Vector can grow or shrink as
 * needed to accommodate adding and removing items after the Vector
 * has been created. The class Vector includes methods for examining
 * individual elements, comparing, searching and extracting parts.
 */

Vector < int > intVector;

void setup()
{
  Serial.begin(9600);
  pinMode(WLED, OUTPUT);  // turn ON wiring hardware LED
  digitalWrite(WLED, HIGH);

  for (int i = 0; i < 255; i++) // add 255 elements from 0 to 254
  {
    intVector.addElement(i);
  }

  Serial.print("The vector's capacity is: ");
  Serial.println(intVector.capacity(), DEC);  // print the vector's capacity

  if (intVector.contains(15) == true)   // check if contains number 15
  {
    Serial.println("The vector contains the element 15");
  }
  Serial.print("The vector's first element is: ");
  Serial.println(intVector.firstElement(), DEC);  // print the vector's first element
  Serial.print("The vector's index for element 30 is: ");
  Serial.println(intVector.indexOf(30), DEC);  // print the vector's element at position 30
  if (intVector.isEmpty() == false)   // check if vector has elements
  {
    Serial.println("The vector has elements");
  }
  Serial.print("The vector's last element is: ");
  Serial.println(intVector.lastElement(), DEC);  // print the vector's last element
  Serial.print("The vector's last index of 10 is: ");
  Serial.println(intVector.lastIndexOf(10), DEC);  // print the vector's last index of 10
  Serial.print("The vector's size is: ");
  Serial.println(intVector.size(), DEC);  // print the vector's size

  if (intVector.add(255) == true)   // add element
  {
    Serial.print("the element was added and now the vector's last element is: ");
    Serial.println(intVector.lastElement(), DEC);  // print the vector's last element
  }

  intVector.addElement(256); // add another element
  Serial.print("now the vector's last element is: ");
  Serial.println(intVector.lastElement(), DEC);  // print the vector's last element

  intVector.insertElementAt(0, 10);  // insert 0 at index 10

  int t = intVector.elementAt(10);  // get the element at index 10
  Serial.print("t is: ");
  Serial.println(t, DEC);  // print its value

  intVector.remove(10);  // remove element at position 10
  t = intVector.get(10);  // get the element at position 10
  Serial.print("t after remove is: ");
  Serial.println(t, DEC);  // print the element at position 10

  intVector.removeElementAt(10);  // remove element at position 10
  t = intVector.get(10);  // get the element at position 10
  Serial.print("t after removeElementAt is: ");  // print the element at position 10
  Serial.println(t, DEC);

  Serial.print("the value of element at position 23 is: ");
  Serial.println(intVector.get(23), DEC);
  if (intVector.removeElement(23) == true)   // remove element 23 from the Vector
  {
    Serial.print("the element at position 23 was removed and the element value after removal is: ");
    Serial.println(intVector.get(23), DEC);
  }

  intVector.setElementAt(10, 5);  // set element at postion 5 with value 10
  t = intVector.get(5);  // get the element at position 10
  Serial.print("element at index 5 is now: ");
  Serial.println(t, DEC);  // print the element at position 10

  intVector.clear();  // clear all elements in the vector
  Serial.print("The vector's size after clear is: ");
  Serial.println(intVector.size(), DEC);  // print the vector's size
}


void loop()
{

}
