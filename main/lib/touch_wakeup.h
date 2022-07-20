#include <driver/touch_pad.h>
#include <esp_log.h>
#include <stdio.h>
#include <unistd.h>
#include <esp_sleep.h>
#include <driver/rtc_io.h>

//static const char* TOUCH_TAG = "TOUCH";


int calibrate(touch_pad_t pad)
{
    uint16_t meas_val;
    uint16_t sum = 0;
    uint16_t average = 0;
    uint16_t threshold = 0;
    printf("calibrating\n");
    for(uint16_t i = 0; i < 28; i++){
        touch_pad_read(TOUCH_PAD_NUM0, &meas_val);
        printf("%d: %d\n", i, meas_val);
        sum += meas_val;
        sleep(0.01);
    }
    average = sum/28;
    printf("average: %d\n", average);
    sleep(2);
    threshold = average - 50;

    touch_pad_config(pad, threshold);

    return 0;

}



void touch_initialize()
{
    printf("Wake up from touch on pad %d\n", esp_sleep_get_touchpad_wakeup_status());
    touch_pad_init();
    touch_pad_config(TOUCH_PAD_NUM0, 0);
    touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    calibrate(TOUCH_PAD_NUM0);

    esp_sleep_enable_touchpad_wakeup();
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    rtc_gpio_isolate(GPIO_NUM_12);
    printf("Starting sleep\n");
    esp_deep_sleep_start();
}

