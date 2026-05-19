#include "cat_state_machine.h"

#include "demo_mode.h"

#include "esp_log.h"

static const char *TAG = "cat_sm";

esp_err_t cat_state_machine_init(void)
{
    ESP_LOGI(TAG, "init");
    return ESP_OK;
}

void cat_state_machine_on_demo_mode(demo_mode_t mode)
{
    switch (mode) {
    case DEMO_MODE_PET_HEAD:
        ESP_LOGI(TAG, "action: 摸头撒娇");
        break;
    case DEMO_MODE_SURPRISE_BRISTLE:
        ESP_LOGI(TAG, "action: 突袭炸毛 (cat side)");
        break;
    case DEMO_MODE_TAIL_PROTEST:
        ESP_LOGI(TAG, "action: 摸尾抗议");
        break;
    case DEMO_MODE_TURNTABLE_SPIN:
        ESP_LOGI(TAG, "note: 转盘由 oracle 板执行");
        break;
    default:
        ESP_LOGI(TAG, "idle");
        break;
    }
}
