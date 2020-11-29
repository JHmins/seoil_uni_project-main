/* i2c - Example
   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples
   See README.md file to get detailed usage of this example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "drv_i2c.h"
#include "drv_sht21.h"
#include "config.h"
/*
static gpio_num_t i2c_gpio_sda = 14;
static gpio_num_t i2c_gpio_scl = 12;
static uint32_t i2c_frequency = 100000;
static i2c_port_t i2c_port = I2C_NUM_0;
*/



//#define HUT21_SENSOR_ADDR 0x40                   /*!< ESP32 slave address, you can set any 7bit value */
#define WRITE_BIT       I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT        I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN    0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS   0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL         0x0                             /*!< I2C ack value */
#define NACK_VAL        0x1                            /*!< I2C nack value */



void i2c_scan(void)
{
	char info[] = "Scanning I2C bus...\r\n";

	printf("%s", info);

	for(uint16_t i = 0; i < 128; i++)
	{
		if( i2c_write_reg(i, 0x00) == ESP_OK)
		{
    		char msg[64];

    		snprintf(msg, sizeof(msg), "0x%02X", i);
    		printf("%s", msg);
		}
        else
		{
			printf("%s", ".");
            ets_delay_us (100);
		}
	}

	printf("%s", "\r\n");
}


esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


esp_err_t i2c_write_reg(uint8_t addr, uint8_t reg)
{
    i2c_cmd_handle_t hCmd = i2c_cmd_link_create();
    i2c_master_start(hCmd);
    i2c_master_write_byte(hCmd, ( addr << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(hCmd, reg, ACK_CHECK_EN);
    i2c_master_stop(hCmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, hCmd, 10 / portTICK_RATE_MS);
    i2c_cmd_link_delete(hCmd);
    return ret;
}



esp_err_t i2c_read_data(uint8_t addr, uint8_t *data_rd, size_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADD_SHT21 << 1) | READ_BIT, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 10 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}


esp_err_t i2c_write_data(uint8_t addr, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADD_SHT21 << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 10 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
