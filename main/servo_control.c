#include <stdio.h>
#include <driver/ledc.h>

void pmw_config(){
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .speed_mode = LEDC_SPEED_MODE_MAX,
        .freq_hz = 50,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
}

void app_main(void)
{

}
