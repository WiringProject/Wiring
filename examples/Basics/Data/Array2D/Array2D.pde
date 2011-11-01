/**
 * Array 2D.
 * 
 * Demonstrates the syntax for creating a two-dimensional (2D) array.
 * Values in a 2D array are accessed through two index values.
 * 2D arrays are useful for storing bitmaps. In this example, each position
 * is holding a number multiple of 5.
 */

int numbers[5][5] = { {5, 10, 15, 20, 25}, // declares an 2D array of 5x5 positions
                      {30, 35, 40, 45, 50},  // with initial values
                      {55, 60, 65, 70, 75},
                      {80, 85, 90, 95, 100},
                      {105, 110, 115, 120, 125}
                    };

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) // print the 2D array using i and j as indexes
  {
    for (int j = 0; j < 5; j++)
    {
      Serial.print(numbers[i][j], DEC);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void loop()
{

}
