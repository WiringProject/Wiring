/**
 * MIDI note player
 * by Tom Igoe
 * 
 * This sketch shows how to use the serial transmit pin (pin 33) to send MIDI note data.
 * If this circuit is connected to a MIDI synth, it will play
 * the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.
 * The circuit:
 * Serial RX (pin 33 on Wiring v1 boards or pin 1 on Wiring S) connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 * Attach a MIDI cable to the jack, then to a MIDI synth, and play music.
 * http://www.arduino.cc/en/Tutorial/MIDI
 */

void setup()
{
  // Set MIDI baud rate:
  Serial.begin(31250);
}

void loop()
{
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++)
  {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity)
{
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

