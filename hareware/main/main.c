#include "demo_mode.h"

#include "esp_log.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Mao.exe firmware start");
    demo_mode_init();
}
