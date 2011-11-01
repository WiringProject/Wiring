/* $Id: WMemory.cpp 1156 2011-06-07 04:01:16Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Implementation of c++ new/delete operators.
|| |
|| | Wiring Common API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  if (ptr)
    free(ptr);
}

void * operator new[](size_t size)
{
  return malloc(size);
}

void operator delete[](void * ptr)
{
  if (ptr)
    free(ptr);
}


int __cxa_guard_acquire(__guard *g)
{
  return !*(char *)(g);
};
void __cxa_guard_release(__guard *g)
{
  *(char *)g = 1;
};
void __cxa_guard_abort(__guard *) {};
void __cxa_pure_virtual(void) {};


int splitString(String &what, int delim,  Vector<long> &splits)
{
  what.trim();
  splits.removeAllElements();
  const char *chars = what.buffer;
  int splitCount = 0; //1;
  for (int i = 0; i < what.length(); i++)
  {
    if (chars[i] == delim) splitCount++;
  }
  if (splitCount == 0)
  {
    splits.addElement(atol(what.buffer));
    return 1;
  }

  int pieceCount = splitCount + 1;

  int splitIndex = 0;
  int startIndex = 0;
  for (int i = 0; i < what.length(); i++)
  {
    if (chars[i] == delim)
    {
      splits.addElement(atol(what.substring(startIndex, i).buffer));
      splitIndex++;
      startIndex = i + 1;
    }
  }
  splits.addElement(atol(what.substring(startIndex, what.length()).buffer));

  return pieceCount;
}


int splitString(String &what, int delim,  Vector<int> &splits)
{
  what.trim();
  splits.removeAllElements();
  const char *chars = what.buffer;
  int splitCount = 0; //1;
  for (int i = 0; i < what.length(); i++)
  {
    if (chars[i] == delim) splitCount++;
  }
  if (splitCount == 0)
  {
    splits.addElement(atoi(what.buffer));
    return(1);
  }

  int pieceCount = splitCount + 1;

  int splitIndex = 0;
  int startIndex = 0;
  for (int i = 0; i < what.length(); i++)
  {
    if (chars[i] == delim)
    {
      splits.addElement(atoi(what.substring(startIndex, i).buffer));
      splitIndex++;
      startIndex = i + 1;
    }
  }
  splits.addElement(atoi(what.substring(startIndex, what.length()).buffer));

  return pieceCount;
}

