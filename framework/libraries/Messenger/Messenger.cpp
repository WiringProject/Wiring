/* $Id: Messenger.cpp 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Thomas Ouellet Fredericks
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Messenger is a "toolkit" that facilitates the parsing of ASCII messages.
|| | Messenger buffers characters until it receives a carriage return (CR).
|| | It then considers the message complete and available.
|| | The message is split into many elements as defined by a separator.
|| | The default separator is the space character, but can be any character other than NULL, LF or CR.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <stdlib.h>

#include <Wiring.h>
#include "Messenger.h"

/*
|| @constructor
|| | Initializes the Messenger to initial state
|| #
*/
Messenger::Messenger()
{
  init(' ');
}

/*
|| @constructor
|| | Initializes the Messenger to initial state
|| #
||
|| @parameter separator The separator is what deliminates the messages into elements
*/
Messenger::Messenger(char separator)
{
  if (separator == 10 || separator == 13 || separator == 0)  separator = 32;
  init(separator);
}

/*
|| @description
|| | Check if there are any element available in the message
|| | You must call process() before calling available()
|| #
||
|| @return True if there are any elements available in the message
*/
uint8_t Messenger::available()
{
  return next();
}

/*
|| @description
|| | Check if a message has been completed and is available
|| | A call to process() erases the leftover elements of the previous message
|| | So, be sure to read what you need from a message after this method return true
|| #
||
|| @return True if there is a message ready
*/
uint8_t Messenger::process(int serialByte)
{
  messageState = 0;
  if (serialByte > 0)
  {
    switch (serialByte)
    {
    case 0:
      break;
    case 10: // LF
      break;
    case 13: // CR
      buffer[bufferIndex] = 0;
      reset();
      messageState = 1;
      current = buffer;
      break;
    default:
      buffer[bufferIndex] = serialByte;
      bufferIndex++;
      if (bufferIndex >= bufferLastIndex) reset();
    }
  }
  if (messageState == 1 && callback != NULL)(*callback)();
  return messageState;
}

/*
|| @description
|| | Return the current element as an int
|| #
||
|| @return The current element as int
*/
int Messenger::readInt()
{
  if (next())
  {
    dumped = 1;
    return atoi(current);
  }
  return 0;
}

/*
|| @description
|| | Return the current element as an long
|| #
||
|| @return The current element as long
*/
long Messenger::readLong() // Added based on a suggestion by G. Paolo Sanino
{
  if (next())
  {
    dumped = 1;
    return atol(current); // atol for long instead of atoi for int variables
  }
  return 0;
}

/*
|| @description
|| | Return the current element as an char
|| #
||
|| @return The current element as char
*/
char Messenger::readChar()
{
  if (next())
  {
    dumped = 1;
    return current[0];
  }
  return 0;
}

/*
|| @description
|| | Copies the element as a string into the the array pointed by the target char array.
|| | maxSize must match the size of the target char array. The element is removed from the completed message.
|| #
*/
void Messenger::copyString(char *string, uint8_t size)
{
  if (next())
  {
    dumped = 1;
    strlcpy(string, current, size);
  }
  else
  {
    if (size) string[0] = '\0';
  }
}

/*
|| @description
|| | Compares the element to the string toCheck.
|| | * If there is a match, the method returns true (1) and removes the element from the completed message.
|| | * If there is no match, the method returns false (0) and does not remove the element from the completed message.
|| #
*/
uint8_t Messenger::checkString(char *string)
{
  if (next())
  {
    if (strcmp(string, current) == 0)
    {
      dumped = 1;
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

/*
|| @description
|| | Attaches a callback function that is executed once a message is completed.
|| | This is the preferred way of working with Messenger (see example)
|| #
||
|| @parameter newFunction The callback that gets called when a mesage is received
*/
void Messenger::attach(messengerCallbackFunction newFunction)
{
  callback = newFunction;
}

/// private methods

void Messenger::init(char separator)
{
  callback = NULL;
  token[0] = separator;
  token[1] = 0;
  bufferLength = MESSENGER_BUFFER_SIZE;
  bufferLastIndex = MESSENGER_BUFFER_SIZE - 1;
  reset();
}

uint8_t Messenger::next()
{
  char * temppointer = NULL;
  switch (messageState)
  {
  case 0:
    return 0;
  case 1:
    temppointer = buffer;
    messageState = 2;
  default:
    if (dumped) current = strtok_r(temppointer, token, &last);
    if (current != NULL)
    {
      dumped = 0;
      return 1;
    }
  }
  return 0;
}


void Messenger::reset()
{
  bufferIndex = 0;
  messageState = 0;
  current = NULL;
  last = NULL;
  dumped = 1;
}

