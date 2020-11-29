#include <stdio.h>
#include <stdint.h>
#include "driver/gpio.h"


#define LED_GPIO   02
#define BOOT_SW_GPIO 0
#define LED_ON      gpio_set_level(LED_GPIO,0)
#define LED_OFF     gpio_set_level(LED_GPIO,1)


void app_main() {
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(BOOT_SW_GPIO, GPIO_MODE_INPUT);

    while(1){

        if(!gpio_get_level(BOOT_SW_GPIO)){
            LED_OFF;
        }
        else {
            LED_ON;
        }

    }

}