#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "config.h"
#include "board.h"
#include "drv_sht21.h"
#include "driver/i2c.h"
#include "drv_touch.h"

#define STATE




void app_main() {
    float temp, humi;    
    char str_buff[30];
    sht21_init();
    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    printf("system boot!\r\n");
    while(1){
        if(temp_humi_Measure_Handler(&temp, &humi)){
            sprintf(str_buff,"temp= %5.2f, hum= %5.2f\r\n",temp, humi);
            printf(str_buff);
            gpio_set_level(LED_GPIO,1);  
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        else {
            gpio_set_level(LED_GPIO,0);  
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }

}
