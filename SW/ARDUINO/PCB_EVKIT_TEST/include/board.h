#pragma onece

#define LED_BUILTIN_PIN     2
#define LED_RED_PIN         33
#define LED_GREEN_PIN       19
#define LED_BLUE_PIN        18

#define LED_BUILTIN_PIN     2
#define LED_RED_PIN         33
#define LED_GREEN_PIN       19
#define LED_BLUE_PIN        18
#define RGB_LED_PIN         23

#define BOOT_SW_PIN         0
#define SW1_PIN             34
#define SW2_PIN             35

#define SD_CS_PIN           15
#define SPI2_SCK_PIN        14
#define SPI2_MOSI_PIN       13
#define SPI2_MISO_PIN       12
#define SD_DECT_PIN         27

#define SCL_PIN             22
#define SDA_PIN             21

#define DAC1_PIN            25
#define DAC2_PIN            26

#define BAT_ADC_PIN         15
#define TC_ADC_P_PIN        39
#define TC_ADC_N_PIN        36

#define CAN_RX_PIN          4
#define CAN_TX_PIN          5

#define UART_RXI2_PIN       16
#define UART_TXO2_PIN       17

#define TOUCH_CH1           T9

#define READ_SW1_PIN        (!digitalRead(SW1_PIN))
#define READ_SW2_PIN        (!digitalRead(SW2_PIN))
#define READ_BOOT_SW_PIN    (!digitalRead(BOOT_SW_PIN))

#define BUILTIN_LED_ON      digitalWrite(LED_BUILTIN_PIN,HIGH)
#define BUILTIN_LED_OFF     digitalWrite(LED_BUILTIN_PIN,LOW)
#define RED_LED_ON          digitalWrite(LED_RED_PIN,HIGH)
#define RED_LED_OFF         digitalWrite(LED_RED_PIN,LOW)
#define GREEN_LED_ON        digitalWrite(LED_GREEN_PIN,HIGH)
#define GREEN_LED_OFF       digitalWrite(LED_GREEN_PIN,LOW)
#define BLUE_LED_ON         digitalWrite(LED_BLUE_PIN,HIGH)
#define BLUE_LED_OFF        digitalWrite(LED_BLUE_PIN,LOW)

#define RED_LED_TOGGLE      (digitalWrite(LED_RED_PIN, !digitalRead(LED_RED_PIN)))
#define GREEN_LED_TOGGLE    (digitalWrite(LED_GREEN_PIN, !digitalRead(LED_GREEN_PIN)))
#define BLUE_LED_TOGGLE     (digitalWrite(LED_BLUE_PIN, !digitalRead(LED_BLUE_PIN)))
#define BUILTIN_LED_TOGGLE  (digitalWrite(LED_BUILTIN_PIN, !digitalRead(LED_BUILTIN_PIN)))

