#include "big_servo.h"

#include "esp_log.h"

static const char *TAG = "big_servo";

esp_err_t big_servo_init(void)
{
    ESP_LOGI(TAG, "init (LEDC / GPIO TBD)");
    return ESP_OK;
}
