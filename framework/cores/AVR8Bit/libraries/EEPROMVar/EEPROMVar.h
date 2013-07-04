/* 
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | This is a library for variables that need to persist through power cycles
|| | It automatically saves to EEPROM every time the value changes
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef EEPROMVar_h
#define EEPROMVar_h

#include <Wiring.h>
#include "EEPROM.h"

class EEPROMAddressCounter {
protected:
  static int availableAddress;
};
int EEPROMAddressCounter::availableAddress = 0;

template<typename T>
class EEPROMVar : 
public EEPROMAddressCounter {
public:
  static const byte IS_INITIALIZED = B10101010;
  
  /*
  || @constructor
  || | Initializes the EEPROMVar
  || #
  || 
  || @parameter init the initial value of this EEPROMVar
  */
  EEPROMVar(T init) 
  {
    address = availableAddress;
    var = init;
    restore();
    availableAddress += sizeof(T) + 1; //make room for the is initialized flag
  }
  
  /*
  || @constructor
  || | save the data of var to the correct EEPROM address
  || #
  */
  void save()
  {
    union {
      byte raw[ sizeof(T) ];
      T data;
    } writer;
    writer.data = var;
    for (byte i=0; i<sizeof(T); i++) 
    {
       EEPROM.write(address + 1 + i, writer.raw[i]);
    }
  }
  
  /*
  || @constructor
  || | set the value of var to the value of the EEPROM address(es)
  || #
  */
  void restore()
  {
    byte init = EEPROM.read(address);
    
    if (init!=EEPROMVar::IS_INITIALIZED) 
    {
      //it was not initialized
      EEPROM.write(address,EEPROMVar::IS_INITIALIZED);
      union {
        byte raw[ sizeof(T) ];
        T data;
      } writer;
      writer.data = var;
      for (byte i=0; i<sizeof(T); i++) 
      {
         EEPROM.write(address + 1 + i, writer.raw[i]);
      }
    }
    //read from EEPROM
    union {
      byte raw[ sizeof(T) ];
      T data;
    } reader;
    for (byte i=0; i<sizeof(T); i++) 
    {
       reader.raw[i] =  EEPROM.read(address + 1 + i);\
    }
    var = reader.data;
  }
  
  operator T () 
  { 
    return var; 
  }
  
  EEPROMVar &operator=(T val) 
  {
    var = val;
  }
  
  void operator++(int) 
  {
    var += T(1); //cast for safety
  }
  
  void operator--(int) 
  {
    var -= T(1); //cast for safety
  }
  
  void operator++() 
  {
    var += T(1); //cast for safety
  }
  
  void operator--() 
  {
    var -= T(1); //cast for safety
  }
  
  template<typename V>
  void operator /= (V divisor) 
  {
    var = var / divisor;
  }
  
  template<typename V>
  void operator *= (V multiplicator) 
  {
    var = var * multiplicator;
  }
  
protected:
  T var;
  int address;
};

#endif
