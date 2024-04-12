#include <TM1637Display.h>
#include "CountDown.h"

CountDown CD(CountDown::MINUTES);

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between display updates
#define REFRESH_DELAY  60000

const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};

TM1637Display display(CLK, DIO);

int mmss(int mins) {
  // returns hhmm format
  return (mins / 60) * 100 + (mins % 60);
}

void setup() {
  display.setBrightness(1);
  display.showNumberDecEx(800, 0b01000000, true);

  // countdown start with minutes as arg
  CD.start(480);
}

void loop() {
  display.showNumberDecEx(mmss(CD.remaining()), 0b01000000, true);
  
  delay(REFRESH_DELAY);
}
