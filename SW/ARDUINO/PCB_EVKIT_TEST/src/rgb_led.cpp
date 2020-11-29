#include "rgb_led.h"
#include "board.h"
#include "Arduino.h"
#include <adafruit_NeoPixel.h>
#include "config.h"
#include "ESPRandom.h"

#define SERIAL_NUM 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(SERIAL_NUM,RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void rgb_led_init(void){
    pixels.begin();
    esp_random();

}


#define RGB_LED_UPDATE_TIME     200

void rgb_led_handler(void){
	uint32_t timeNow;
	static uint32_t restart_time=0;
	static bool over_flow_f =false;    
    timeNow=millis();
    
	
   	if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - RGB_LED_UPDATE_TIME)) ) {
        over_flow_f= time_end_calculation(timeNow, RGB_LED_UPDATE_TIME, &restart_time);
        BLUE_LED_TOGGLE;
        pixels.setPixelColor(0, pixels.Color(random(2)*127 , random(2)*127 , random(2)*127 )); 
        pixels.setPixelColor(1, pixels.Color(random(5)*51 , random(5)*51 , random(5)*51 )); 
        pixels.show(); // This sends the updated pixel color to the hardware.
    }
}