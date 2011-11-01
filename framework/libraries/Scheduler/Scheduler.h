/* $Id: Scheduler.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Provides an easy way of scheduling function calls somewhere in the future.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Wiring.h>

//provide a typedef for a void function pointer
typedef void (*function)();

///internal datatype
typedef struct schedule_action_s
{
  function action;
  unsigned long time;
  unsigned long delay;
  //assignment operator
  schedule_action_s& operator=(const schedule_action_s& rhs)
  {
    action = rhs.action;
    time = rhs.time;
    delay = rhs.delay;
    return *this;
  }
  //boolean equality
  bool operator==(const schedule_action_s& rhs) const
  {
    return (action == rhs.action && time == rhs.time && delay == rhs.delay);
  }
} schedule_action;

template<int maxFunctionsToCall>
class Scheduler
{
  public:
    /*
    || @constructor
    || | Initialize the Scheduler
    || #
    */
    Scheduler()
    {
      action[0].action = NULL;
      action[0].delay = 65535;
      action[0].time = 0;
      currentSize = 0;
    }

    /*
    || @description
    || | Check to see if it's time to call any of the functions
    || #
    */
    void update()
    {
      //flush/update all
      for (byte i = 0; i < currentSize; i++)
      {
        //it is time to call the function associated with action[i]
        if ((millis() - action[i].time) > action[i].delay)
        {
          action[i].action(); //call function
          //this was the last action in queue
          if (i == 0 && currentSize == 1)
          {
            currentSize = 0;
          }
          //this is the second action of two possible, only one left
          else if (i == 1 && currentSize == 2)
          {
            currentSize = 1;
          }
          //the last action has executed, cut it off
          else if (i + 1 == currentSize)
          {
            currentSize--;
          }
          //all other elements
          else if (i + 1 < currentSize)
          {
            action[i] = action[i + 1];
            defragment(); //get rid of the two copies in memory
          }
        }
      }
    }
    /*
    || @description
    || | Schedule a functioncall in 'time' milliseconds.
    || #
    ||
    || @parameter userAction  a function that should be called in time ms
    || @parameter time        the time to wait before calling the userAction
    */
    void schedule(function userAction, unsigned long time)
    {
      if (currentSize < maxFunctionsToCall)
      {
        action[currentSize].action = userAction;
        action[currentSize].delay = time;
        action[currentSize].time = millis();
        currentSize++;
      }
    }

  private:
    //Removes all redundant actions from memory
    void defragment()
    {
      byte defrag = 0;
      for (byte i = 0; i < currentSize; i++)
      {
        if (i + 1 < currentSize && action[i] == action[i + 1])
        {
          defrag = i + 1;
          while (defrag + 1 < currentSize)
          {
            action[defrag] = action[defrag + 1];
            defrag++;
          }
          currentSize--;
        }
      }
    }

    schedule_action action[maxFunctionsToCall];
    byte currentSize;
};

#endif
// SCHEDULER_H
