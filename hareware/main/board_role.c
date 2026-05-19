#include "board_role.h"

#include "hardware_config.h"
#include "pca9685.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "nvs.h"
#include "sdkconfig.h"

static const char *TAG = "board_role";
static board_role_t s_role = BOARD_ROLE_UNKNOWN;

static board_role_t board_role_read_strap(void);
static board_role_t board_role_read_nvs(void);

board_role_t board_role_detect(void)
{
#if CONFIG_BOARD_ROLE_FORCE_ORACLE
    s_role = BOARD_ROLE_ORACLE;
    ESP_LOGI(TAG, "role forced: oracle");
    return s_role;
#elif CONFIG_BOARD_ROLE_FORCE_CAT
    s_role = BOARD_ROLE_CAT;
    ESP_LOGI(TAG, "role forced: cat");
    return s_role;
#endif

    board_role_t role = board_role_read_nvs();
    if (role != BOARD_ROLE_UNKNOWN) {
        ESP_LOGI(TAG, "role from NVS: %s", board_role_name(role));
        s_role = role;
        return s_role;
    }

    role = board_role_read_strap();
    if (role == BOARD_ROLE_ORACLE || role == BOARD_ROLE_CAT) {
        ESP_LOGI(TAG, "role from strap GPIO%d: %s", (int)HW_BOARD_STRAP_GPIO,
                 board_role_name(role));
        s_role = role;
        return s_role;
    }

    if (pca9685_probe()) {
        ESP_LOGI(TAG, "role from I2C PCA9685 -> oracle");
        s_role = BOARD_ROLE_ORACLE;
        return s_role;
    }

    ESP_LOGI(TAG, "role default -> cat");
    s_role = BOARD_ROLE_CAT;
    return s_role;
}

static board_role_t board_role_read_strap(void)
{
    gpio_config_t io = {
        .pin_bit_mask = 1ULL << HW_BOARD_STRAP_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    if (gpio_config(&io) != ESP_OK) {
        return BOARD_ROLE_UNKNOWN;
    }
    int level = gpio_get_level(HW_BOARD_STRAP_GPIO);
    if (level == HW_BOARD_STRAP_ORACLE_LEVEL) {
        return BOARD_ROLE_ORACLE;
    }
    return BOARD_ROLE_CAT;
}

static board_role_t board_role_read_nvs(void)
{
    nvs_handle_t nvs;
    if (nvs_open("hareware", NVS_READONLY, &nvs) != ESP_OK) {
        return BOARD_ROLE_UNKNOWN;
    }
    uint8_t role = BOARD_ROLE_UNKNOWN;
    if (nvs_get_u8(nvs, "board_role", &role) != ESP_OK || role > BOARD_ROLE_CAT) {
        nvs_close(nvs);
        return BOARD_ROLE_UNKNOWN;
    }
    nvs_close(nvs);
    return (board_role_t)role;
}

board_role_t board_role_get(void)
{
    if (s_role == BOARD_ROLE_UNKNOWN) {
        return board_role_detect();
    }
    return s_role;
}

const char *board_role_name(board_role_t role)
{
    switch (role) {
    case BOARD_ROLE_ORACLE:
        return "oracle";
    case BOARD_ROLE_CAT:
        return "cat";
    default:
        return "unknown";
    }
}
