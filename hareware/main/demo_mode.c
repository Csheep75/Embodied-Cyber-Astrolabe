#include "demo_mode.h"

#include "big_servo.h"
#include "cat_state_machine.h"
#include "comm_espnow.h"
#include "hall_sensor.h"
#include "mg90s.h"
#include "oracle_state_machine.h"
#include "power_monitor.h"
#include "sensor_tof.h"
#include "sensor_touch.h"
#include "stepper_28byj.h"
#include "ws2812_led.h"

#include "esp_log.h"

static const char *TAG = "demo";

esp_err_t demo_mode_init(void)
{
    ESP_LOGI(TAG, "hardware bring-up (demo order)");

    (void)power_monitor_init();
    (void)mg90s_init();
    (void)big_servo_init();
    (void)stepper_28byj_init();
    (void)hall_sensor_init();
    (void)ws2812_led_init();
    (void)sensor_tof_init();
    (void)sensor_touch_init();
    (void)comm_espnow_init();
    (void)cat_state_machine_init();
    (void)oracle_state_machine_init();

    return ESP_OK;
}
