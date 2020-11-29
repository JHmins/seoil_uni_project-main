#include <Arduino.h>
#include "board.h"

void setup() {
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
 }

void loop() {
  BUILTIN_LED_TOGGLE;
  RED_LED_TOGGLE;
  GREEN_LED_TOGGLE;
  BLUE_LED_TOGGLE;
  delay(100);
}