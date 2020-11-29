#include "Arduino.h"
#include "config.h"
#include "board.h"
#include "adc.h"

#define ADC_MEASURING_CYCLE_TIME    100

bool adc_handler(int * adc_result){
	uint32_t timeNow;
	static uint32_t restart_time=0;
	static bool over_flow_f =false;    
    timeNow=millis();
    
	
   	if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - ADC_MEASURING_CYCLE_TIME)) ) {
        over_flow_f= time_end_calculation(timeNow, ADC_MEASURING_CYCLE_TIME, &restart_time);
        *adc_result = analogRead(TC_ADC_P_PIN);
        return true;

    }
    return false;


}