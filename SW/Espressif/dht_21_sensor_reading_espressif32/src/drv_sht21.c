#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "driver/i2c.h"
#include "config.h"
#include "drv_i2c.h"
#include "drv_sht21.h"



#define SHT21_MEASURE_WAIT 120

#define ERROR_TEMP_VALUE -55;
#define ERROR_HUMI_VALUE 0;

float temperature, humi;


typedef enum{
	SHT21_14BIT_RESOLUTION
}SHT21_resolution_e;


//static uint8_t SHT21_conversion_time;

static uint8_t sht21_CalcCRC(uint8_t *data,uint8_t nbrOfBytes);
bool time_end_calculation(uint32_t time_now, uint32_t time_interval, uint32_t * restart_time);


static void sht21_user_reg_set(void);

typedef enum {
	SHT21_INIT,
	TEMP_START,
	TEMP_CONVERSION_WAIT,
	HUMI_CONVERSION_WAIT,
}SHT21status_e;

#define I2C_ERROR_RST_COUNT	5
#define RE_TRY_COUNT	3
bool temp_humi_Measure_Handler(float * pTemp, float * pHumi) {
	uint32_t timeNow;
	static uint32_t restart_time=0;
	static SHT21status_e status = SHT21_INIT;
	static uint8_t error_count=0, stop_err_cont=0;
	static uint8_t cmd;
	uint16_t raw_value=0;
	uint8_t data[4];
	bool return_value =false;
	static bool over_flow_f =false;
//	static uint32_t last_update_time;

	timeNow= esp_timer_get_time();
	switch((uint8_t) status) {
		case SHT21_INIT:
			error_count =0;
			i2c_master_init();
			if(!sht21_sw_reset()) {
				goto ERROR;
			}
			sht21_user_reg_set();
			status = TEMP_START;
			break;
		
		case TEMP_START:
			cmd = SHT21_TRIGGER_T_MEASURE;
			if(i2c_write_reg(ADD_SHT21,cmd) != ESP_OK) {
				goto ERROR;
			}
			over_flow_f= time_end_calculation(timeNow, SHT21_MEASURE_WAIT, &restart_time);			
			status = TEMP_CONVERSION_WAIT;
			break;
		
		case TEMP_CONVERSION_WAIT:
//		if(timeNow-timeStart > SHT21_MEASURE_WAIT){
			if(timeNow >= restart_time && !(over_flow_f  && timeNow > (0xFFFFFFFF - SHT21_MEASURE_WAIT)) ) {
				memset(data,0,sizeof(data));
				if(i2c_read_data(ADD_SHT21, data, 4) != ESP_OK) {
						goto ERROR;
				}
				if(data[0] + data[1] + data[2] ==0) {		
					goto ERROR;
				}
				
				if(sht21_CalcCRC(data,2) == data[2]){
					raw_value=((uint16_t)data[0]<<8)|data[1];
					*pTemp = ((float)raw_value*175.72)/65536-46.85;
					
					//start humidity measuring
					cmd = SHT21_TRIGGER_RH_MEASURE;
					if(i2c_write_reg(ADD_SHT21, cmd)!=ESP_OK) {
						goto ERROR;
					}
					status = HUMI_CONVERSION_WAIT;
				}
				else {		// crc error 
					cmd = SHT21_TRIGGER_T_MEASURE;
					if(i2c_write_reg(ADD_SHT21, cmd)!=ESP_OK) {
						goto ERROR;
					}
				}
				over_flow_f= time_end_calculation(timeNow, SHT21_MEASURE_WAIT, &restart_time);			
			}
			break;
			
		case HUMI_CONVERSION_WAIT:
			if(timeNow >= restart_time && !(over_flow_f  && timeNow < (0xFFFFFFFF - SHT21_MEASURE_WAIT)) ) {
				memset(data,0,sizeof(data));
				if(i2c_read_data(ADD_SHT21, data,4) != ESP_OK) {
						goto ERROR;
				}
				if(data[0] + data[1] + data[2] ==0) {		
					goto ERROR;
				}
				
				if(sht21_CalcCRC(data,2) == data[2]){
					error_count=0;		
					stop_err_cont =0;
					return_value = true;
//					last_update_time = timeNow;		
					raw_value=((uint16_t)data[0]<<8)|data[1];
					* pHumi = ((float)raw_value*125)/65536-6;
					
					if(*pHumi > 100){
						*pHumi =100;		//asic max value 118 %RH
					}
					else if(*pHumi < 0){
						*pHumi =0;		//asic min value -6 %RH
					}
//					cmd = SHT21_TRIGGER_T_MEASURE;
//					sht21_Transmit(&cmd, 1);
					status=TEMP_START;
				}
				else{	//humidity crc error
					cmd = SHT21_TRIGGER_RH_MEASURE;
					if(i2c_write_reg(ADD_SHT21, cmd)!=ESP_OK) {
						goto ERROR;
					}
					over_flow_f= time_end_calculation(timeNow, SHT21_MEASURE_WAIT, &restart_time);			
				}
			}
			break;
		
		default:
			status=SHT21_INIT;
			break;
	}

	
	return return_value;
	
	ERROR :
		error_count++;
		if(error_count > I2C_ERROR_RST_COUNT) {
				status =SHT21_INIT;
				stop_err_cont++;
				if(stop_err_cont >= RE_TRY_COUNT) {
					stop_err_cont=0;
					status =SHT21_INIT;
					//error value set
					*pTemp = ERROR_TEMP_VALUE;
					*pHumi =ERROR_HUMI_VALUE;
					return true;
				}
		}
		else {		
//			if(sht21_Transmit(&cmd, 1)!=ESP_OK) {
			if(i2c_write_reg(ADD_SHT21, cmd)!=ESP_OK) {
					error_count++;
				over_flow_f= time_end_calculation(timeNow, SHT21_MEASURE_WAIT, &restart_time);			
			}
		}
		return return_value;
}



void sht21_init(void){
//  Wire.begin(sda, scl); 
//  Wire.setClock(100000);   
    i2c_master_init();
	//delay(100);
	ets_delay_us(100);
	i2c_scan();
	sht21_sw_reset();
	delay(100);
	sht21_user_reg_set();
}

static void sht21_user_reg_set(void) {
	uint8_t reg	= SHT21_RH_14BIT_TEMP_12BIT + SHT21_VDD_225_BIG + SHT21_ON_CHIP_HEATER_DISABLE \
	+ SHT21_OTP_RELOAD_DISABLE;
	i2c_write_reg(ADD_SHT21, reg);
}

bool sht21_sw_reset(void) {
//	uint8_t txd_cmd_reset[2]={CMD_SHT21_RESET,};

//	if(i2c_write_data(txd_cmd_reset,1)==HAL_OK){
	if(i2c_write_reg(ADD_SHT21, CMD_SHT21_RESET)==ESP_OK){
		delay(50);
		return true;
	}
	return false;
}




static uint8_t sht21_CalcCRC(uint8_t *data,uint8_t nbrOfBytes){
    // CRC
    //const u16t POLYNOMIAL = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001
    uint8_t byteCtr,bit,crc;
    crc = 0;

    //calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
       crc ^= (data[byteCtr]);
       for (bit = 8; bit > 0; --bit)
       {
          if (crc & 0x80) crc = (crc << 1) ^ 0x131;
          else 		crc = (crc << 1);
       }
    }
    return(crc);
}
