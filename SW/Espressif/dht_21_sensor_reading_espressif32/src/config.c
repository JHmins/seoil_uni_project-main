#include <stdio.h>
#include <stdint.h>
//#include <string.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "sdkconfig.h"

#include "config.h"            // SD Card ESP32

#define PUSH_SHORT_TIME  50
#define PUSH_LONG_TIME   800



void delay(uint32_t ms)
{
  vTaskDelay(ms / portTICK_PERIOD_MS);
}

//btn_status_e btn_stat;

bool time_end_calculation(uint32_t time_now, uint32_t time_interval, uint32_t * restart_time) {
    * restart_time = time_now + time_interval;
    if((uint64_t)time_now + time_interval  <= 0xFFFFFFFF) { //time overf flow가 아닐경우
        return false;
    }
    else {  //time over flow 일경우
        return true;
    }
}

/*

void button_read_handler(void) {
  uint32_t millis_count;
  static int16_t btn_tick;
  static uint8_t befor_tick;
  static bool befor_btn_status;


  millis_count = millis();
      
  if((uint8_t)millis_count != befor_tick){
    befor_tick = (uint8_t)millis_count;
    if(!READ_SW_PIN) {
      if(befor_btn_status > READ_SW_PIN) {
        btn_stat =  PUSH_START;
      }
      btn_tick++;
      befor_btn_status =false;
      
      if(btn_tick > PUSH_LONG_TIME) { //risin edge
        btn_tick=0;
        btn_stat = PUSH_LONG;
      }
    }
    else {
      if(btn_tick > PUSH_SHORT_TIME && btn_stat == PUSH_START) {  //risin edge
        btn_tick=0;
        btn_stat = PUSH_SHORT;
      }
      btn_tick=0;
      befor_btn_status =true;
      btn_stat == PUSH_NONE;
      
    }
  }
}
*/