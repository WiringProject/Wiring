/**
 * Arrays.
 * 
 * An array is a list of data. Each piece of data in an array
 * is identified by an index number representing its position in
 * the array. Arrays are zero based, which means that the first
 * element in the array is [0], the second element is [1], and so on.
 * In this example, three arrays are created "array" "numbers" and "floats"
 * filled with char, int and float values. This data is displayed
 * on the Wiring console.
 */

char array[20];
int numbers[20];
float floats[20];

void setup()
{
  for (int i = 0; i < 20; i++)
  {
    // fill "array" array with lower case characters starting woith the 'a'
    array[i] = 'a' + i;
    // fill the "numbers" array with integers
    numbers[i] = i;
    // fill the "floats" array with floating point numbers
    floats[i] = float(i);
  }

  Serial.begin(9600);

  for (int i = 0; i < 20; i++) // print array
  {
    Serial.print(array[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < 20; i++) // print numbers
  {
    Serial.print(numbers[i], DEC);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < 20; i++) // print floats
  {
    Serial.print(floats[i]);
    Serial.print(" ");
  }
}

void loop()
{
}

