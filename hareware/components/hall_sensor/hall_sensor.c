#include "hall_sensor.h"
#include "hardware_config.h"

#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "hall";

esp_err_t hall_sensor_init(void)
{
    gpio_config_t io = {
        .pin_bit_mask = 1ULL << HW_HALL_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    esp_err_t err = gpio_config(&io);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "init gpio %d", (int)HW_HALL_GPIO);
    }
    return err;
}

bool hall_sensor_is_triggered(void)
{
    return gpio_get_level(HW_HALL_GPIO) == 0;
}
