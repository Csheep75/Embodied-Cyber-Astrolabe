#include "board_bringup.h"

#include "board_role.h"
#include "cat_state_machine.h"
#include "comm_espnow.h"
#include "hardware_config.h"
#include "oracle_state_machine.h"
#include "power_monitor.h"
#include "sensor_tof.h"
#include "sensor_touch.h"
#include "ws2812_led.h"

#include "big_servo.h"
#include "esp_log.h"
#include "hall_sensor.h"
#include "mg90s.h"
#include "stepper_28byj.h"

static const char *TAG = "bringup";

static esp_err_t bringup_oracle(void)
{
    ESP_LOGI(TAG, "Oracle peripherals");
    (void)mg90s_init();
    (void)big_servo_init();
    (void)stepper_28byj_init();
    (void)hall_sensor_init();
    (void)oracle_state_machine_init();
    return ESP_OK;
}

static esp_err_t bringup_cat(void)
{
    ESP_LOGI(TAG, "Cat peripherals");
    (void)sensor_tof_init();
    (void)sensor_touch_init();
    (void)cat_state_machine_init();
    return ESP_OK;
}

esp_err_t board_bringup(void)
{
    board_role_t role = board_role_detect();

    (void)power_monitor_init();
    (void)ws2812_led_init();
    (void)comm_espnow_init();

    switch (role) {
    case BOARD_ROLE_ORACLE:
        bringup_oracle();
        break;
    case BOARD_ROLE_CAT:
        bringup_cat();
        break;
    default:
        ESP_LOGW(TAG, "unknown role, skip peripherals");
        break;
    }

    ESP_LOGI(TAG, "ready role=%s hw=%s", board_role_name(role), HW_CONFIG_VERSION);
    return ESP_OK;
}
