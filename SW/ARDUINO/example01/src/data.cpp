#include <Arduino.h>
#include "data.h"


data_t data;



void init_data(void){
    data.temp =0;
    data.humi =0;
}