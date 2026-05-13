#include "ws2812_led.h"

#include "esp_log.h"

static const char *TAG = "ws2812";

esp_err_t ws2812_led_init(void)
{
    ESP_LOGI(TAG, "init (RMT / bit-bang TBD)");
    return ESP_OK;
}
