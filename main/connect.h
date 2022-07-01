// Connects the ESP32 to a wifi
#include <esp_wifi.h>
#include <unistd.h>
#include <esp_err.h>
#include <nvs_flash.h>


#define SSID "Pixel 3a"
#define PASS "100ma100"


void connect_ESP32(){
    nvs_flash_init(); // what is this doing??
    // initialize wifi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_wifi_set_mode(WIFI_MODE_STA); // Station mode
    // configure SSID and password
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = SSID,
            .password = PASS,
        },
    };
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

    esp_wifi_start();
    sleep(1);
    printf("Connecting...\n");
    while(esp_wifi_connect() != ESP_OK){} // try to connect to SSID
    printf("connected to %s\n", SSID);   
}