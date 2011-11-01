/* $Id: FiniteStateMachine.cpp 1235 2011-09-11 19:49:14Z abrevig $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Provides an easy way of making finite state machines.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "FiniteStateMachine.h"

/*
|| @constructor
|| | Update only state
|| | Set the initial state of this State
|| #
||
|| @parameter updateFunction the function to call when this state updates
*/
State::State(void (*updateFunction)())
{
  userEnter = 0;
  userUpdate = updateFunction;
  userExit = 0;
}

/*
|| @constructor
|| | Set the initial state of this State
|| #
||
|| @parameter enterFunction  the function to call when this state enters
|| @parameter updateFunction the function to call when this state updates
|| @parameter exitFunction   the function to call when this state exits
*/
State::State(void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)())
{
  userEnter = enterFunction;
  userUpdate = updateFunction;
  userExit = exitFunction;
}

/*
|| @description
|| | Enter this state
|| | Call the userEnter function callback
|| #
*/
void State::enter()
{
  if (userEnter)
  {
    userEnter();
  }
}

/*
|| @description
|| | Update this state
|| | Call the userUpdate function callback
|| #
*/
void State::update()
{
  if (userUpdate)
  {
    userUpdate();
  }
}

/*
|| @description
|| | Exit this state
|| | Call the userExit function callback
|| #
*/
void State::exit()
{
  if (userExit)
  {
    userExit();
  }
}


/*
|| @constructor
|| | Set the initial state of this Finite State Machine
|| #
||
|| @parameter current The initial state of the FSM
*/
FiniteStateMachine::FiniteStateMachine(State& current)
{
  needToTriggerEnter = true;
  currentState = nextState = &current;
  stateChangeTime = 0;
}

/*
|| @description
|| | Update this FSM
|| | It will call enter/update/exit on the current at the correct time
|| #
*/
FiniteStateMachine& FiniteStateMachine::update()
{
  //simulate a transition to the first state
  //this only happens the first time update is called
  if (needToTriggerEnter)
  {
    currentState->enter();
    needToTriggerEnter = false;
  }
  else
  {
    if (currentState != nextState)
    {
      immediateTransitionTo(*nextState);
    }
    currentState->update();
  }
  return *this;
}

/*
|| @description
|| | Have the FSM schedule a transition for the next update()
|| #
||
|| @parameter state The state to transit to
*/
FiniteStateMachine& FiniteStateMachine::transitionTo(State& state)
{
  nextState = &state;
  stateChangeTime = millis();
  return *this;
}

/*
|| @description
|| | Have the FSM transit to the next state immediatly
|| #
||
|| @parameter state The state to transit to
*/
FiniteStateMachine& FiniteStateMachine::immediateTransitionTo(State& state)
{
  currentState->exit();
  currentState = nextState = &state;
  currentState->enter();
  stateChangeTime = millis();
  return *this;
}

/*
|| @description
|| | Get the current state of this FSM
|| #
*/
State& FiniteStateMachine::getCurrentState() const
{
  return *currentState;
}

/*
|| @description
|| | Check if this FSM is in the State state
|| #
||
|| @parameter state The state to check against
||
|| @return true if the FSM is in State state
*/
bool FiniteStateMachine::isInState(State &state) const
{
  return (&state == currentState);
}

/*
|| @description
|| | Get the current state of this FSM
|| #
||
|| @return The time this state has been active
*/
unsigned long FiniteStateMachine::timeInCurrentState() const
{
  if (stateChangeTime)
  {
    return millis() - stateChangeTime;
  }
  return 0;
}
