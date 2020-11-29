#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO    2
#define LED_ON      gpio_set_level(LED_GPIO,0)
#define LED_OFF     gpio_set_level(LED_GPIO,1)

void app_main() {
    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    printf("system start!\r\n");
    while(1){
        LED_ON;
        vTaskDelay(500/portTICK_PERIOD_MS);
        LED_OFF;
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
