#include "stepper_28byj.h"
#include "hardware_config.h"

#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "stepper";

esp_err_t stepper_28byj_init(void)
{
    const gpio_num_t pins[] = {
        HW_STEPPER_IN1,
        HW_STEPPER_IN2,
        HW_STEPPER_IN3,
        HW_STEPPER_IN4,
    };

    for (size_t i = 0; i < sizeof(pins) / sizeof(pins[0]); i++) {
        gpio_config_t io = {
            .pin_bit_mask = 1ULL << pins[i],
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
        esp_err_t err = gpio_config(&io);
        if (err != ESP_OK) {
            return err;
        }
    }
    ESP_LOGI(TAG, "gpio init ok");
    return ESP_OK;
}
