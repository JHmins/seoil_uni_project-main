/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
 #define LED_BUILTIN 2
 #define BOOT_SW 0
void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOOT_SW, INPUT);
}
void loop()
{
 // turn the LED on (HIGH is the voltage level)
  if(!digitalRead(BOOT_SW)){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
