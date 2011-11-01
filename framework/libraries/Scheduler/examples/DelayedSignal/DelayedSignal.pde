/**
 * DelayedSignal
 * by BREVIG http://alexanderbrevig.com
 * 
 * Display a way to delay a led signal on serial recieve.
 */

#include <Scheduler.h>

Scheduler<10> scheduler;              //create a scheduler that can schedule 10 function calls at the time

const byte ledPin = WLED;             //LED on onboard led

void setup()
{
  Serial.begin(9600);                 //Iitialize the UART
  pinMode(ledPin,OUTPUT);             //set pin 13 to OUTPUT
}

void loop()
{
  scheduler.update();                 //update the scheduler, maybe it is time to execute a function?
  
  if (Serial.available())
  {            //if we have recieved anything on the Serial
    scheduler.schedule(setHigh,500);  //schedule a setHigh call in 500 milliseconds
    Serial.flush();                   //flush Serial so we do not schedule multiple setHigh calls
  }
}

void setHigh()
{
  digitalWrite(ledPin,HIGH);          //set ledPin HIGH
  scheduler.schedule(setLow,500);     //schedule setLow to execute in 500 milliseconds
}

void setLow()
{
  digitalWrite(ledPin,LOW);           //set ledPin LOW
}
