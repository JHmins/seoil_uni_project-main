/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include "Wire.h"            // SD Card ESP32
#include "config.h"            // SD Card ESP32

#include "drv_sht21.h"
#include "webpage.h"

// Libraries to get time from NTP Server
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define CAMERA_MODEL_AI_THINKER // Has PSRAM

// Define deep sleep options
uint64_t uS_TO_S_FACTOR = 1000000;  // Conversion factor for micro seconds to seconds
// Sleep for 10 minutes = 600 seconds
uint64_t TIME_TO_SLEEP = 10;



// Save reading number on RTC memory

#define SENSOR_DATA_PRINTER_CYCLE_TIME 1000
void sensor_status_print_handler(void){
  static uint32_t restart_time=0;  
  uint32_t timeNow;
  static bool over_flow_f =false;  
  char value_str[80];
  timeNow =millis();
  if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - SENSOR_DATA_PRINTER_CYCLE_TIME)) ) {
   over_flow_f= time_end_calculation(timeNow, SENSOR_DATA_PRINTER_CYCLE_TIME, &restart_time);
    sprintf(value_str, "Temp= %6.2f℃, Humi= %5.2f%RH%%", temperature, humi);
    Serial.println(value_str);
  }
}
    
void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(115200);

  sht21_init(I2C_SCL, I2C_SDA);

  pinMode(BUTTON_GPIO, INPUT_PULLUP);

  pinMode(LED_GPIO, OUTPUT);
  
  init_webServer();
//  init_NTPClient();
}

typedef enum {
  SYSTEM_INIT,
  SYSTE_IDLE,
  LOGGING,
}e_system_status;

#define SENSOR_READ_CYCLE   2
void loop() {
  static uint32_t restart_time=0;  
  uint32_t timeNow;
  static bool over_flow_f =false;
  static e_system_status sys_status = SYSTEM_INIT;

  timeNow =millis();

  if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - SENSOR_READ_CYCLE)) ) {
   over_flow_f= time_end_calculation(timeNow, SENSOR_READ_CYCLE, &restart_time);
   if(temp_humi_Measure_Handler(&temperature, &humi)) {
      webServer_handler();
   }
  }
//  sensor_status_print_handler();
}
