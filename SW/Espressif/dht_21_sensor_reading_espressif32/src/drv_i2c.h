#pragma once

#define I2C_MASTER_NUM              I2C_NUM_1
#define I2C_MASTER_SDA_IO           21
#define I2C_MASTER_SCL_IO           22
#define I2C_MASTER_FREQ_HZ          100000
#define I2C_MASTER_TX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */

#define WRITE_BIT       I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT        I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN    0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS   0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL         0x0                             /*!< I2C ack value */
#define NACK_VAL        0x1                            /*!< I2C nack value */


void i2c_scan(void);
esp_err_t i2c_master_init(void);
esp_err_t i2c_read_data(uint8_t addr, uint8_t *data_rd, size_t size);
esp_err_t i2c_write_data(uint8_t addr,uint8_t *data_wr, size_t size);
esp_err_t i2c_write_reg(uint8_t addr, uint8_t cmd);
