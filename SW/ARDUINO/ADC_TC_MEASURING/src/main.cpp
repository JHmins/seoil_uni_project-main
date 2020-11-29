//https://github.com/krzychb/esp32-lna/blob/master/Arduino/esp32-lna-thermocouple-basic/esp32-lna-thermocouple-basic.ino
#include <Arduino.h>
#include "ESP32LNA.h"
#include "drv_sht21.h"
#include "board.h"

#define ADC_WIDTH_BIT              (10)
#define ADC_ATTEN             (ADC_0db)
#define ADC_SAMPLE_COUNT          (256)
#define LNA_STAGE_1_CYCLES       (1024)
#define LNA_STAGE_3_CYCLES         (64)

#define COLD_JUCTION_TEMPERATURE   (18)

#define AMS2302_PIN                 (5)


const adc_mv_cal_t thk_cal = {
    -1.000,  // bottom mV input signal value  
      1694,  // bottom ADC reading
     2.599,  // top mV input signal value
      3680   // top ADC reading
};


// data source: http://cn.omega.com/learning/ITS-90T-CPoly.html
#define POLY_N (6)
const double poly_k[] = {
    0,          // 0
    2.508e-2,   // 1
    7.860e-8,   // 2
   -2.503e-10,  // 3
    8.315e-14,  // 4
   -1.228e-17   // 5
};


double calc_temperature(float milivolts)
{
    double temperature = poly_k[0];

    for (int i=1; i<POLY_N; i++) {
        temperature += poly_k[i] * pow(1000*milivolts, i);
    }
    return temperature;
}

ESP32LNA lna;

void setup()
{
  sht21_init(SCL_PIN, SDA_PIN);
  Serial.begin(115200);
  delay(1000);
  
  Serial.print("Initializing LNA...");
  Serial.println( lna.init(ADC_WIDTH_BIT, ADC_ATTEN) ? "done" : "failed");
}


void loop()
{
  char logString[60];
  float temp, humi;
      
  while (1) {
    int adc_sum = 0;
    temp_humi_Measure_Handler(&temp, &humi);
    for (int i = 0; i < ADC_SAMPLE_COUNT; i++) {
        adc_sum += lna.getValue(LNA_STAGE_1_CYCLES, LNA_STAGE_3_CYCLES);
    }
  
    adc_sum /= ADC_SAMPLE_COUNT;
    double milivolts = lna.adc_to_mv(thk_cal, ADC_WIDTH_BIT, adc_sum);
    double temperature = calc_temperature(milivolts);
    int16_t temperature_cj = temp;
    temperature += temperature_cj;
    sprintf(logString, "Thermocouple: %2.3f mV, %2.0f oC, Cold junction temperature: %2d oC, ADC raw count: %5d\n",
            milivolts, temperature, temperature_cj, adc_sum);
    Serial.print(logString);
    delay(1000);
  }
}