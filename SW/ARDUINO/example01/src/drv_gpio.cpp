#include <Arduino.h>
#include "drv_gpio.h"
#include "board.h"


void init_gpio(void){
    pinMode(LED_RED_PIN,OUTPUT);
    pinMode(LED_GREEN_PIN,OUTPUT);
    pinMode(LED_BLUE_PIN,OUTPUT);
    pinMode(LED_BUILTIN_PIN,OUTPUT);
    pinMode(SW1_PIN,INPUT);
    pinMode(SW2_PIN,INPUT);
    pinMode(BOOT_SW_PIN,INPUT);
}
