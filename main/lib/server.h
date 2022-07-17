#include <esp_log.h>
#include <esp_http_server.h>
#include "index.h"
#include "servo.h"

static const char *SERVER_TAG = "SERVER";
 

/* Our URI handler function to be called during GET /uri request */
esp_err_t get_handler_lock(httpd_req_t *req)
{
    /* Send a simple response
    */
    const char* resp = (const char*) req->user_ctx;
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    lock_door();
    return ESP_OK;
}

esp_err_t get_handler_unlock(httpd_req_t *req)
{
    /* Send a simple response
    */
    const char* resp = (const char*) req->user_ctx;
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    unlock_door();
    return ESP_OK;
}


// URI handler structure for GET /unlock
httpd_uri_t locked = {
    .uri      = "/locked",
    .method   = HTTP_GET,
    .handler  = get_handler_lock,
    .user_ctx = &locked_page
};


// URI handler structure for GET /lock
httpd_uri_t unlocked = {
    .uri      = "/unlocked",
    .method   = HTTP_GET,
    .handler  = get_handler_unlock,
    .user_ctx = &unlocked_page
};

// URI handler structure for GET /root
httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_handler_lock,
    .user_ctx = &locked_page
};


/* Function for starting the webserver */
void start_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        ESP_LOGI(SERVER_TAG, "SERVER STARTED.");
        httpd_register_uri_handler(server, &unlocked);
        httpd_register_uri_handler(server, &locked);
        httpd_register_uri_handler(server, &root);
    }
    /* If server failed to start, handle will be NULL */
    else{
        ESP_LOGI(SERVER_TAG, "FAILED TO START SERVER.");
    }
}

/* Function for stopping the webserver */
void stop_webserver(httpd_handle_t server)
{
    if (server) {
        /* Stop the httpd server */
        httpd_stop(server);
    }
}