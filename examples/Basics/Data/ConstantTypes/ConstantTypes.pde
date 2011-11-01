/**
 * ConstantTypesExample.pde
 * A Wiring Sketch to demonstrate the ConstantTypes types/library.
 * Original sketch (and library, named FlashString) by Mikal Hart.
 * Modified by Brett Hagman <bhagman@roguerobotics.com>.
 * 
 * This sketch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This sketch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this source code.  If not, see <http://www.gnu.org/licenses/>.
 * Notes:
 * [bh] I changed the library to ConstantTypes to be more generic.
 * In the sketch, I added documentation (more detail for freeMemory()
 * too!).
 */


void setup()
{
  // Excerpt from Ulysses, by James Joyce

  ConstantString big_string = Constant(
                                "Stately, plump Buck Mulligan came from the stairhead, bearing a bowl of\n"
                                "lather on which a mirror and a razor lay crossed. A yellow dressinggown,\n"
                                "ungirdled, was sustained gently behind him on the mild morning air. He\n"
                                "held the bowl aloft and intoned:\n"
                                "--_Introibo ad altare Dei_.\n"
                                "Halted, he peered down the dark winding stairs and called out coarsely:\n"
                                "--Come up, Kinch! Come up, you fearful jesuit!\n"
                                "Solemnly he came forward and mounted the round gunrest. He faced about\n"
                                "and blessed gravely thrice the tower, the surrounding land and the\n"
                                "awaking mountains. Then, catching sight of Stephen Dedalus, he bent\n"
                                "towards him and made rapid crosses in the air, gurgling in his throat\n"
                                "and shaking his head. Stephen Dedalus, displeased and sleepy, leaned\n"
                                "his arms on the top of the staircase and looked coldly at the shaking\n"
                                "gurgling face that blessed him, equine in its length, and at the light\n"
                                "untonsured hair, grained and hued like pale oak.\n");

  IntTable sine_table = IntTable(
                          0, 6, 12, 18, 25, 31, 37, 43, 49, 56, 62, 68, 74, 80, 86, 92, 97, 103, 109, 115, 120, 126, 131, 136, 142,
                          147, 152, 157, 162, 167, 171, 176, 181, 185, 189, 193, 197, 201, 205, 209, 212, 216, 219, 222, 225,
                          228, 231, 234, 236, 238, 241, 243, 244, 246, 248, 249, 251, 252, 253, 254, 254, 255, 255, 255, 256,
                          255, 255, 255, 254, 254, 253, 252, 251, 249, 248, 246, 244, 243, 241, 238, 236, 234, 231, 228, 225,
                          222, 219, 216, 212, 209, 205, 201, 197, 193, 189, 185, 181, 176, 171, 167, 162, 157, 152, 147, 142,
                          136, 131, 126, 120, 115, 109, 103, 97, 92, 86, 80, 74, 68, 62, 56, 49, 43, 37, 31, 25, 18, 12, 6, 0, -6,
                          -12, -18, -25, -31, -37, -43, -49, -56, -62, -68, -74, -80, -86, -92, -97, -103, -109, -115, -120,
                          -126, -131, -136, -142, -147, -152, -157, -162, -167, -171, -176, -181, -185, -189, -193, -197,
                          -201, -205, -209, -212, -216, -219, -222, -225, -228, -231, -234, -236, -238, -241, -243, -244,
                          -246, -248, -249, -251, -252, -253, -254, -254, -255, -255, -255, -256, -255, -255, -255, -254,
                          -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238, -236, -234, -231, -228, -225,
                          -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185, -181, -176, -171, -167, -162,
                          -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103, -97, -92, -86, -80, -74, -68,
                          -62, -56, -49, -43, -37, -31, -25, -18, -12, -6, -6, -12, -18, -25, -31, -37, -43, -49, -56, -62,
                          -68, -74, -80, -86, -92, -97, -103, -109, -115, -120, -126, -131, -136, -142, -147, -152, -157,
                          -162, -167, -171, -176, -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219, -222,
                          -225, -228, -231, -234, -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254,
                          -254, -255, -255, -255, -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246,
                          -244, -243, -241, -238, -236, -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201,
                          -197, -193, -189, -185, -181, -176, -171, -167, -162, -157, -152, -147, -142, -136, -131, -126,
                          -120, -115, -109, -103, -97, -92, -86, -80, -74, -68, -62, -56, -49, -43, -37, -31, -25, -18, -12, -6);

  Serial.begin(115200);
  // This demonstrates that all the big data is really in Constant memory and not consuming RAM
  Serial.print(Constant("Despite there being an enormous amount of data in this program, the available RAM is still "));
  Serial.println(freeMemory());

  // Example 1: Inline Constant strings
  Serial.println(Constant("\n****Example 1: This is an example of an inline Constant string."));

  // Example 2: Named Constant strings
  Serial.println(Constant("\n****Example 2: Using named Constant strings:"));

  // 2.b Find the length of Constant string (internally uses strlen_P)

  Serial.print(Constant("The size of the big string is "));
  Serial.println(big_string.length());
  Serial.print(Constant("But the RAM used by the big string is only "));
  Serial.println(sizeof(big_string));

  // 2.c Access individual characters of the Constant string using array [] notation

  int comma_count = 0;
  for (int i = 0; big_string[i]; ++i) // inspect each character in the string
    if (big_string[i] == ',')
      ++comma_count;
  Serial.print(Constant("There are "));
  Serial.print(comma_count);
  Serial.println(Constant(" commas in the big string."));

  // 2.d Print the string
  Serial.println(Constant("The big string is, quote:"));
  Serial.println(big_string);

  // Example 3: Constant arrays
  Serial.println(Constant("\n****Example 3: Using named Constant arrays:"));

  // 3.a Print out the array
  Serial.println(Constant("The sine table is "));
  for (int i = 0; i < sine_table.count(); ++i)
    Serial.println(sine_table[i]);

  // 3.b Determine the size of the array
  Serial.print(Constant("The sine array contains "));
  Serial.print(sine_table.count());
  Serial.println(Constant(" integers."));
  Serial.print(Constant("But the RAM used by the sine array is only "));
  Serial.println(sizeof(sine_table));

  // 3.c Access individual elements of the array using [] notation
  int maximum = sine_table[0];
  for (int i = 1; i < sine_table.count(); ++i)
    if (sine_table[i] > maximum)
      maximum = sine_table[i];
  Serial.print(Constant("The peak value of the sine wave is "));
  Serial.println(maximum);
}

void loop()
{
  // Empty - so this does nothing in an endless loop.
}


int freeMemory()
{
  // Available memory:
  //
  // No malloc():
  //  RAMSTART                 RAMEND
  //  | .data | .bss | FREE | stack |
  //
  // With malloc():
  //  RAMSTART                        RAMEND
  //  | .data | .bss | heap | FREE | stack |
  //
  // To calculate the size of the "FREE" section, we simply subtract
  // the end of the .bss section (__bss_end) from the stack
  // pointer (from a local variable).
  //
  // If we are using malloc(), then we need to subtract the end of the
  // heap (__brkval) from the stack pointer.
  // See the avr-libc malloc reference for more information.
  // http://www.nongnu.org/avr-libc/user-manual/malloc.html
  // http://forum.pololu.com/viewtopic.php?f=10&t=989&view=unread#p4218

  extern unsigned int __bss_end;  // top of the static variable memory
  extern void *__brkval;  // top of the malloc heap (if needed)

  int free_memory;        // the address of this variable will give us the
  // stack pointer, which is where our memory "ends"

  if ((int)__brkval == 0)  // if using malloc(), __brkval needs to be used
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);
  return free_memory;
}


