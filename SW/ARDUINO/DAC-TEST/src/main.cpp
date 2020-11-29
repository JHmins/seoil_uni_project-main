#include <Arduino.h>

#define DAC2  26
void setup() {
}

void loop() {
  static int i;

  i=i%256;
  dacWrite(DAC2,i);
  delay(50);
  i++;
}