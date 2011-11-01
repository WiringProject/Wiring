/** 
 * NewSoftSerial 
 * 
 * Demonstrates the use of software serial ports with two ports
 */

#include <NewSoftSerial.h>

NewSoftSerial nss(4, 5);
NewSoftSerial nss2(6, 7);

void setup()
{
  nss2.begin(4800);
  nss.begin(4800);
  Serial.begin(115200);
}

void loop()
{
  // Every 10 seconds switch from 
  // one serial GPS device to the other
  if ((millis() / 10000) % 2 == 0)
  {
    if (nss.available())
    {
      Serial.print(nss.read(), BYTE);
    }
  }

  else
  {
    if (nss2.available())
    {
      Serial.print(nss2.read(), BYTE);
    }
  }
}

