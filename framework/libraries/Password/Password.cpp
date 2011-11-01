/* $Id: Password.cpp 1198 2011-06-14 21:08:27Z bhagman $
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

#include "Password.h"
/*
|| @constructor
|| | Initialize this Password
|| #
||
|| @parameter pass the initial password
*/
Password::Password(char* pass)
{
  set(pass);
  reset();
}

/*
|| @description
|| | Set the password
|| #
||
|| @parameter pass the password
*/
void Password::set(char* pass)
{
  target = pass;
}

/*
|| @description
|| | Check if a string is equal to the password
|| #
||
|| @parameter pass the guess
||
|| @return true if guess is equal to password
*/
bool Password::is(char* pass)
{
  byte i = 0;
  while (*pass && i < MAX_PASSWORD_LENGTH)
  {
    guess[i] = pass[i];
    i++;
  }
  return evaluate();
}

/*
|| @description
|| | Append a char to the current guess
|| #
||
|| @parameter character  to append to the current guess
||
|| @return false if there is no more space available in the buffer
*/
bool Password::append(char character)
{
  if (currentIndex + 1 == MAX_PASSWORD_LENGTH)
  {
    return false;
  }
  else
  {
    guess[currentIndex++] = character;
    guess[currentIndex] = STRING_TERMINATOR; //ensure a valid c string
  }
  return true;
}

/*
|| @description
|| | Reset the guess
|| #
*/
void Password::reset()
{
  currentIndex = 0;
  guess[currentIndex] = STRING_TERMINATOR;
}

/*
|| @description
|| | Is the current guessed password equal to the target password?
|| #
||
|| @return true if the guessed password is valid
*/
bool Password::evaluate()
{
  char pass = target[0];
  char guessed = guess[0];
  for (byte i = 1; i < MAX_PASSWORD_LENGTH; i++)
  {

    //check if guessed char is equal to the password char
    if (pass == STRING_TERMINATOR && guessed == STRING_TERMINATOR)
    {
      return true; //both strings ended and all previous characters are equal
    }
    else if (pass != guessed || pass == STRING_TERMINATOR || guessed == STRING_TERMINATOR)
    {
      return false; //difference OR end of string has been reached
    }

    //read next char
    pass = target[i];
    guessed = guess[i];
  }
  return false; //a 'true' condition has not been met
}

/*
|| @description
|| | Set the password
|| #
||
|| @parameter pass the new password
||
|| @return this Password
*/
Password &Password::operator=(char* pass)
{
  set(pass);
  return *this;
}

/*
|| @description
|| | Check this Password for equality against a string
|| #
||
|| @parameter pass the guess
||
|| @return true if the guess is equal to this Password
*/
bool Password::operator==(char* pass)
{
  return is(pass);
}

/*
|| @description
|| | Check this Password for inequality against a string
|| #
||
|| @parameter pass the guess
||
|| @return true if the guess is not equal to this Password
*/
bool Password::operator!=(char* pass)
{
  return !is(pass);
}

/*
|| @description
|| | Append a char to the current guess
|| #
||
|| @parameter character  to append to the current guess
||
|| @return this Password
*/
Password &Password::operator<<(char character)
{
  append(character);
  return *this;
}


