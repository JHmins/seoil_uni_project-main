#include <Arduino.h>
#include "board.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "drv_gpio.h"
#include "drv_sht21.h"
#include "data.h"


//#define OS_DELAY(x)  vTaskDelay(x/portTICK_RATE_MS)
void led_task(void *Parameter);
void msg_task(void *Parameter);


void setup() {
  init_gpio();
  sht21_init(SCL_PIN,SDA_PIN);
  Serial.begin(115200);
  xTaskCreate(led_task, "led_task", 1024, NULL, 1, NULL);
  xTaskCreate(msg_task, "msg_task", 4096, NULL, 3, NULL);
}

void loop() {
}

void led_task(void *Parameter){
  while (1){
    RED_LED_TOGGLE;
    delay(500);

  }
}

void msg_task(void *Parameter){
  init_data();
//  float temp, humi;
  char buff[50];
  while (1){
    if(temp_humi_Measure_Handler(&data.temp, &data.humi)){
      sprintf(buff,"temp=%.2f, humi=%.2f\r\n",data.temp, data.humi);
      Serial.print(buff);
        delay(500);
        GREEN_LED_TOGGLE;
    }
    else {
      delay(10);
    }
  }
}