#include <TM1637Display.h>
#include "CountDown.h"

CountDown CD(CountDown::MINUTES);

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3
#define LED_PIN 5
#define BUTTON_PIN 2

// The amount of time (in milliseconds) between display updates
#define REFRESH_DELAY  60000

volatile byte ledState = LOW;

long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

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
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, RISING);
  
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  display.setBrightness(0);
  display.showNumberDecEx(800, 0b01000000, true);

  // countdown start with minutes as arg
  CD.start(480);
  CD.stop();
}

void loop() {
  display.showNumberDecEx(mmss(CD.remaining()), 0b01000000, true);
  
  delay(REFRESH_DELAY);
}

void handleButtonPress() {
  ledState = !ledState;
  if(ledState == LOW) {
    CD.stop();
  } else {
    CD.start(CD.remaining());
  }
  digitalWrite(LED_PIN, ledState);
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    last_micros = micros();
    handleButtonPress();
  }
}
