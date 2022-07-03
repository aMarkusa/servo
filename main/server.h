// functions fopr setting up server

#include <esp_http_server.h>
#include <esp_err.h>
#include <esp_log.h>

static const char* TAG = "Server";

// GET handler

static esp_err_t hello_get_handler(httpd_req_t *req){
    char* buf;
    size_t buf_len;

    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1; // +1 for null-terminator
    if (buf_len > 1) {
        buf = malloc(buf_len);
        if(!buf){
            return ESP_FAIL;
        }
        /* Copy null terminated value string into buffer */
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
            ESP_LOGI(TAG, "Found header => Host: %s", buf);
        }
         
        free(buf);
    }
    return ESP_OK;
}

// Hello world handle
static const httpd_uri_t hello = {
    .uri = "/hello",
    .method = HTTP_GET,
    .handler = hello_get_handler,
    .user_ctx = "Hello World! From Markus"
};

// Start server
static httpd_handle_t start_webserver(void){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        httpd_register_uri_handler(server, &hello);

        return server;
    }
    printf("hello\n\n");
    return NULL;
}

