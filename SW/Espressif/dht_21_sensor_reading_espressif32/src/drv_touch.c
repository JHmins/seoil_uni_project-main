#include "board.h"
#include "driver/touch_pad.h"
#include "drv_touch.h"
#include "config.h"

#define TOUCH_PAD_CH      9


void touch_init(void){
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    touch_pad_config(TOUCH_PAD_CH, TOUCH_THRESH_NO_USE);
#if TOUCH_FILTER_MODE_EN
    touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
#endif

}

void tp_read_handler(void){
    uint16_t touch_value;
    uint16_t touch_filter_value;
#if TOUCH_FILTER_MODE_EN
//    printf("Touch Sensor filter mode read, the output format is: \nTouchpad num:[raw data, filtered data]\n\n");
#else
    printf("Touch Sensor normal mode read, the output format is: \nTouchpad num:[raw data]\n\n");
#endif
#if TOUCH_FILTER_MODE_EN
            // If open the filter mode, please use this API to get the touch pad count.
            touch_pad_read_raw_data(TOUCH_PAD_CH, &touch_value);
            touch_pad_read_filtered(TOUCH_PAD_CH, &touch_filter_value);
            printf("T%d:[%4d,%4d] ", TOUCH_PAD_CH, touch_value, touch_filter_value);
#else
            touch_pad_read(TOUCH_PAD_CH, &touch_value);
            printf("T%d:[%4d] ", TOUCH_PAD_CH, touch_value);
#endif
        printf("\n");
        delay(200);
    
}
