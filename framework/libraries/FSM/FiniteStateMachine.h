/* $Id: FiniteStateMachine.h 1198 2011-06-14 21:08:27Z bhagman $
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

#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <Wiring.h>

#define NO_ENTER (0)
#define NO_UPDATE (0)
#define NO_EXIT (0)

#define FSM FiniteStateMachine

//define the functionality of the states
class State
{
  public:
    State(void (*updateFunction)());
    State(void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)());
    //State( byte newId, void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );

    //void getId();
    void enter();
    void update();
    void exit();

  private:
    //byte id;
    void (*userEnter)();
    void (*userUpdate)();
    void (*userExit)();
};

//define the finite state machine functionality
class FiniteStateMachine
{
  public:
    FiniteStateMachine(State& current);

    FiniteStateMachine& update();
    FiniteStateMachine& transitionTo(State& state);
    FiniteStateMachine& immediateTransitionTo(State& state);

    State& getCurrentState() const;
    bool isInState(State &state) const;

    unsigned long timeInCurrentState() const;

  private:
    bool 	needToTriggerEnter;
    State* 	currentState;
    State* 	nextState;
    unsigned long stateChangeTime;
};

#endif
// FINITESTATEMACHINE_H
