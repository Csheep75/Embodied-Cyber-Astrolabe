#include "oracle_state_machine.h"

#include "demo_mode.h"

#include "esp_log.h"

static const char *TAG = "oracle_sm";

esp_err_t oracle_state_machine_init(void)
{
    ESP_LOGI(TAG, "init");
    return ESP_OK;
}

void oracle_state_machine_on_demo_mode(demo_mode_t mode)
{
    switch (mode) {
    case DEMO_MODE_SURPRISE_BRISTLE:
        ESP_LOGI(TAG, "action: 炸毛撑起 (20kg / servos)");
        break;
    case DEMO_MODE_TURNTABLE_SPIN:
        ESP_LOGI(TAG, "action: 灵犀转盘旋转");
        break;
    case DEMO_MODE_PET_HEAD:
    case DEMO_MODE_TAIL_PROTEST:
        ESP_LOGI(TAG, "note: 表情动作由 cat 板执行");
        break;
    default:
        ESP_LOGI(TAG, "idle");
        break;
    }
}
