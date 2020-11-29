#include "Arduino.h"
#include "config.h"
#include "board.h"
#include "dac.h"

#define DAC_UPDATE_TIME 10

void dac_handler(void){
	uint32_t timeNow;
    static int i=0;
	static uint32_t restart_time=0;
	static bool over_flow_f =false;    
    timeNow=millis();
    
	
   	if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - DAC_UPDATE_TIME)) ) {
        over_flow_f= time_end_calculation(timeNow, DAC_UPDATE_TIME, &restart_time);
        i=i%256;
        dacWrite(DAC1_PIN,i);
        i++;
    }

}