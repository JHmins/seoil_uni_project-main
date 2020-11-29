#include <Arduino.h>
#include "board.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define OS_DELAY(x)  vTaskDelay(x/portTICK_RATE_MS)

void task1(void *Parameter){
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  while(1){
    BUILTIN_LED_TOGGLE;
    RED_LED_TOGGLE;
    OS_DELAY(200);
  }
}

void task2(void *Parameter){
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  while(1){
    OS_DELAY(200);
    GREEN_LED_TOGGLE;
    BLUE_LED_TOGGLE;
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task1, "task1", 1024, NULL, 1, NULL);
  xTaskCreate(task2, "task2", 1024, NULL, 1, NULL);
}

void loop(){
}