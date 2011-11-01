#include <Wiring.h>

int main(void) 
{
  // Hardware specific initializations.
  boardInit();

  // User defined setup routine
  setup();
  // User defined loop routine
  for (;;)
    loop();
}
