/**
 * HelloFluentPrint
 * by BREVIG http://alexanderbrevig.com
 * 
 */

#include <FluentPrint.h>

FluentPrint printer(&Serial);

void setup() 
{
  printer.print("test").print("other");
}

void loop() 
{
}
