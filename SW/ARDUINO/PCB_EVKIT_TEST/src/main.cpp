#include "Arduino.h"
#include "sd_test.h"
#include "gpio.h"
#include "rgb_led.h"
#include "board.h"
#include "drv_sht21.h"
#include "dac.h"
#include "adc.h"

void setup() {
  Serial.begin(115200);
  sd_test();
  gpio_init();
  rgb_led_init();
  sht21_init(SCL_PIN, SDA_PIN);
}

void loop() {
  float temp, humi;
  int rawADC;
  char buff[50];
  adc_handler(&rawADC);
  if(temp_humi_Measure_Handler(&temp, &humi)) {
    sprintf(buff,"temp=%.2f, humi=%.2f, rawADC=%d\r\n", temp, humi, rawADC);
    Serial.print(buff);
  }
  rgb_led_handler();
  gpio_handler();
  dac_handler();
  delay(1);   //esp32의 arduino frame work 는 Free rtos가 포팅되어 있어 delay가 없을 경우 os 리소스 반환이 없어 문제가 되어 삽입
}
