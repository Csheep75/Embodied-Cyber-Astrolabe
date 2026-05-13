#include "mg90s.h"
#include "pca9685.h"

#include "esp_log.h"

static const char *TAG = "mg90s";

esp_err_t mg90s_init(void)
{
    esp_err_t err = pca9685_init();
    if (err != ESP_OK) {
        return err;
    }
    ESP_LOGI(TAG, "init (PCA9685 channels TBD)");
    return ESP_OK;
}
