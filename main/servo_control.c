// Code used to control a servo 

#include <stdio.h>
#include <driver/ledc.h>
#include <unistd.h>
#include <stdio.h>
#include "connect.h"


#define PWM_PIN 4  // GPIO-Pin used for pwm signal for servo

void pmw_config(){
    // Set up timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .freq_hz = 50,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    
    // Set up PWM-channel
    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .gpio_num = PWM_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel = LEDC_TIMER_0,
    };
    ledc_channel_config(&ledc_channel);
    
    sleep(1);

}

void open_door(){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 26);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void close_door(){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 10);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void app_main(void)
{
    pmw_config();
    init_wifi();
    /*while(1){
        open_door();
        sleep(2);
        close_door();
        sleep(2);
    }*/
}

