#pragma once
#include <stdbool.h>
//#include "measure.h"

//==ADDRESS==
//#define ADD_SHT21 0x40
const uint8_t ADD_SHT21 = 0x40;


extern float temperature, humi;


// Sensor commands
#define CMD_TMP_HLD   		0xE3
#define CMD_HUM_HLD   		0xE5
#define CMD_TMP_NOHLD		0xF3
#define CMD_HUM_NOHLD	0xF5
#define CMD_WR_REG    			0xE6
#define CMD_RD_REG    			0xE7
#define CMD_SOFT_RST  		0xFE



#define SHT21_I2C_ADD (0x40<<1)




//----------- USER REGISTER----------

#define SHT21_RH_14BIT_TEMP_12BIT							0x00
#define SHT21_RH_8BIT_TEMP_12BIT								0x01
#define SHT21_RH_10BIT_TEMP_13BIT							0x80
#define SHT21_RH_11BIT_TEMP_11BIT							0x81
#define SHT21_VDD_225_BIG															(1<<6)
#define SHT21_VDD_225_SMALL												0
#define SHT21_ON_CHIP_HEATER_ENABLE				(1<<2)
#define SHT21_ON_CHIP_HEATER_DISABLE			0
#define SHT21_OTP_RELOAD_DISABLE							(1<<1)
#define SHT21_OTP_RELOAD_ENABLE							0



#define SHT21_TRIGGER_T_MEASURE 			0xF3
#define SHT21_TRIGGER_RH_MEASURE	 	0xF5




//==CMD==
#define CMD_SHT21_TRIGGER_T_MEASURE 		0xF3
#define CMD_SHT21_TRIGGER_RH_MEASURE 	0xF5
#define CMD_SHT21_WRITE_USER_REG 						0xE6
#define CMD_SHT21_READ_USER_REG 						0xE7
#define CMD_SHT21_RESET 															0xFE

//==BIT config==
#define DISABLE_OIP_RELOAD 													0x01 //1
#define ENABLE_ON_CHIP_HEATER 									0x00 //2
//#define RESERVED 																						0x00 //3,4,5
#define VDD_2_25V 																						0x00 //6

#define RESOLUTION_14BIT 0x00 //7,0
#define BIT_MASK 0x81 //7,0�� ����Ʈ�ϱ�����

#define SHT21_14BIT_CONV_TIME 85



//extern SHT21_resolution_e resolution;

bool temp_humi_Measure_Handler(float * pTemp, float * pHumi);
bool temp_humi_Measure_ring(float * pTemp, float * pHumi) ;
bool sht21_sw_reset(void);

//uint8_t SHT21_CalcCrc(uint8_t *data,uint8_t nbrOfBytes);
//void I2C_SHT32_resolution_set(SHT21_resolution_e resolution);
void sht21_init(uint8_t scl, uint8_t sda);
