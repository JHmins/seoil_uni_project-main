#include <Arduino.h>

#define ADC_CH1_PIN 36
 #define LED_BUILTIN 02
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int adc;

  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  adc = analogRead(ADC_CH1_PIN);
  Serial.println(adc);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
}