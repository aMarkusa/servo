// Code used to control a servo 

#include "connect.h"
#include "server.h"
#include "servo.h"

//static const char *MAIN_TAG = "MAIN";

void app_main(void)
{
    pmw_config();
    init_wifi();
    start_webserver();

    /*while(1){
        open_door();
        sleep(2);
        close_door();
        sleep(2);
    }*/
}

