#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "Wire.h"            // SD Card ESP32
#include "config.h"            // SD Card ESP32

#define PUSH_SHORT_TIME  50
#define PUSH_LONG_TIME   800


btn_status_e btn_stat;

bool time_end_calculation(uint32_t time_now, uint32_t time_interval, uint32_t * restart_time) {
    * restart_time = time_now + time_interval;
    if((uint64_t)time_now + time_interval  <= 0xFFFFFFFF) { //time overf flow가 아닐경우
        return false;
    }
    else {  //time over flow 일경우
        return true;
    }
}
