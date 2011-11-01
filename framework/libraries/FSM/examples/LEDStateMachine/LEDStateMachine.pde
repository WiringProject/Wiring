/**
 * LEDStateMachine
 * by BREVIG http://alexanderbrevig.com
 * 
 * Use a Finite State Machine for controlling an LED
 * This example is intended as an illustration, you should not use an FSM to control a single LED
 */
 
#include <FiniteStateMachine.h>
#include <Button.h>
#include <LED.h>

const byte NUMBER_OF_STATES = 4; //how many states are we cycling through?

//initialize states
State On = State(ledOn);
State Off = State(ledOff); 
State FadeIn = State(ledFadeIn);
State FadeOut = State(ledFadeOut); 

FSM ledStateMachine = FSM(On);     //initialize state machine, start in state: On

Button button = Button(12,BUTTON_PULLUP); //initialize the button (wire between pin 12 and ground)
LED led = LED(11);                 //initialize the LED
byte buttonPresses = 0;            //counter variable, hols number of button presses

void setup(){ /*nothing to setup*/ }

//poor example, but then again; it's just an example
void loop()
{
  if (button.uniquePress())
  {
    //increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
    buttonPresses = ++buttonPresses % NUMBER_OF_STATES; 
    switch (buttonPresses)
    {
      case 0: ledStateMachine.transitionTo(On); break;
      case 1: ledStateMachine.transitionTo(Off); break;
      case 2: ledStateMachine.transitionTo(FadeIn); break;
      case 3: ledStateMachine.transitionTo(FadeOut); break;
    }
  }
  ledStateMachine.update();
}

void ledOn(){ led.on(); }
void ledOff(){ led.off(); }
void ledFadeIn(){ led.fadeIn(500); }
void ledFadeOut(){ led.fadeOut(500); }
