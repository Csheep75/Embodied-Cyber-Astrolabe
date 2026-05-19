#include "demo_mode.h"

#include "board_bringup.h"
#include "board_role.h"
#include "demo_console.h"
#include "hardware_config.h"

#include "esp_log.h"

static const char *TAG = "demo";
static demo_mode_t s_demo_mode = DEMO_MODE_IDLE;

demo_mode_t demo_mode_get(void)
{
    return s_demo_mode;
}

esp_err_t demo_mode_set(demo_mode_t mode, bool broadcast_peer)
{
    if (mode >= DEMO_MODE_MAX) {
        return ESP_ERR_INVALID_ARG;
    }
    s_demo_mode = mode;
    ESP_LOGI(TAG, "mode=%d role=%s", (int)mode, board_role_name(board_role_get()));

    if (broadcast_peer) {
        extern esp_err_t comm_espnow_send_demo_mode(demo_mode_t m);
        (void)comm_espnow_send_demo_mode(mode);
    }
    return ESP_OK;
}

esp_err_t demo_mode_init(void)
{
    ESP_LOGI(TAG, "unified firmware hw=%s", HW_CONFIG_VERSION);
    esp_err_t err = board_bringup();
    demo_console_start();
    return err;
}
