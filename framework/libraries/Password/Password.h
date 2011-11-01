/* $Id: Password.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Handle passwords easily.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef PASSWORD_H
#define PASSWORD_H

#include <Wiring.h>

#define MAX_PASSWORD_LENGTH 20

#define STRING_TERMINATOR '\0'

class Password
{
  public:
    Password(char* pass);

    void set(char* pass);
    bool is(char* pass);
    bool append(char character);
    void reset();
    bool evaluate();

    //char* getPassword();
    //char* getGuess();

    //operators
    Password &operator=(char* pass);
    bool operator==(char* pass);
    bool operator!=(char* pass);
    Password &operator<<(char character);

  private:
    char* target;
    char guess[ MAX_PASSWORD_LENGTH ];
    byte currentIndex;
};

#endif
// PASSWORD_H
