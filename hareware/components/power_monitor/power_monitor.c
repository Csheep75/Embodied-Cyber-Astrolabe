#include "power_monitor.h"

#include "esp_log.h"

static const char *TAG = "power_mon";

esp_err_t power_monitor_init(void)
{
    ESP_LOGI(TAG, "init (ADC channel TBD)");
    return ESP_OK;
}
