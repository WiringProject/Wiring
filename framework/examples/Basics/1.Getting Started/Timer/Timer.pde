/**
 * Blink the Wiring board LED
 * by Yann Dirson <ydirson@free.fr>
 *
 * turns on and off the Wiring board LED, with
 * intervals of 1 second, using a 16bit timer
 * interrupt to avoid burning electrons with active wait.
 *
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 * it is also possible to use the WLED constant with the
 * digitalWrite command: digitalWrite(WLED, HIGH). WLED will be the
 * correct pin in the current board selected in the
 * Tools -> Board menu.
 */

void timer1_irq()
{
  static int led = LOW;
  led = (led==LOW) ? HIGH : LOW;
  digitalWrite(WLED, led);
}

void setup() {
  pinMode(WLED, OUTPUT);

  Timer1.setMode(0b0100);  // CTC mode with OCR1A
  Timer1.setClockSource(CLOCK_PRESCALE_1024);
  Timer1.setOCR(CHANNEL_A, F_CPU/1024);
  Timer1.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, timer1_irq);
  Timer1.enableInterrupt(INTERRUPT_COMPARE_MATCH_A);

  // disable unused clocks
  Timer0.setClockSource(CLOCK_STOP);
  Timer3.setClockSource(CLOCK_STOP);
}

void loop() {
  sleep_mode();
}
