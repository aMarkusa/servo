#include <driver/touch_pad.h>
#include <esp_log.h>
#include <stdio.h>
#include <unistd.h>

//static const char* TOUCH_TAG = "TOUCH";

void touch_initialize()
{
    touch_pad_init();
    touch_pad_config(TOUCH_PAD_NUM0, 0);
    touch_pad_sw_start();
}

void measure()
{
    uint16_t meas_val;
    touch_initialize();
    touch_pad_filter_start(10);
    while(1){
        touch_pad_read_raw_data(TOUCH_PAD_NUM0, &meas_val);
        printf("VALUE: %d\n", meas_val);
        sleep(1);
    }
}