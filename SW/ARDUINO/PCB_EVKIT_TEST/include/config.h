#pragma once

#define LOGGING_CYCLE_TIME  1000



typedef enum {
  PUSH_NONE,
  PUSH_START,
  PUSH_SHORT,
  PUSH_LONG,
  BTN_READ,
}btn_status_e;



extern btn_status_e btn_stat;

bool time_end_calculation(uint32_t time_now, uint32_t time_interval, uint32_t * restart_time);
void button_read_handler(void);
