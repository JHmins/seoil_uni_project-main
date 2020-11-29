#pragma once

#define LED_GPIO   02
#define LED_ON      digitalWrite(LED_GPIO,0)
#define LED_OFF      digitalWrite(LED_GPIO,1)
#define LOGGING_CYCLE_TIME  1000

#define BUTTON_GPIO 11
#define READ_SW_PIN      digitalRead(BUTTON_GPIO)

#define I2C_SDA 21
#define I2C_SCL 22



typedef enum {
  PUSH_NONE,
  PUSH_START,
  PUSH_SHORT,
  PUSH_LONG,
  BTN_READ,
}btn_status_e;



extern btn_status_e btn_stat;

bool time_end_calculation(uint32_t time_now, uint32_t time_interval, uint32_t * restart_time);
