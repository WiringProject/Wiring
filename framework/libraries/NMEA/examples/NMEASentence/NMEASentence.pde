/**
 * This example illustates access to all sentence types,
 * using the NMEA library. It assumes that a GPS receiver
 * is connected to serial port 'Serial1' at 4800 bps.
 */
 
#include <nmea.h>

NMEA gps(ALL);    // GPS data connection to all sentence types

void setup() {
  Serial.begin(9600);
  Serial1.begin(4800);
}

void loop() {
  if (Serial1.available() > 0 ) {
    // read incoming character from GPS and feed it to NMEA type object
    if (gps.decode(Serial1.read())) {
      // full sentence received
      Serial.print ("Sentence = ");
      Serial.println (gps.sentence());
      Serial.print ("Datatype = ");
      Serial.println (gps.term(0));
      Serial.print ("Number of terms = ");
      Serial.println (gps.terms());
    }
  }
}
