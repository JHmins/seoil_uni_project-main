#include "Arduino.h"
#include "gpio.h"
#include "board.h"



void gpio_init(void){
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BOOT_SW_PIN, INPUT);
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
}


void gpio_handler(void){
  if(READ_SW1_PIN){
    RED_LED_ON;
  }
  else {
    RED_LED_OFF;
  }  
  if(READ_SW2_PIN){
    GREEN_LED_ON;
  }
  else {
    GREEN_LED_OFF;
  }  
}