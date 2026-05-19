#include "pca9685.h"
#include "hardware_config.h"

#include "driver/i2c_master.h"
#include "esp_log.h"

static const char *TAG = "pca9685";
static i2c_master_bus_handle_t s_bus;
static i2c_master_dev_handle_t s_dev;
static bool s_inited;

static esp_err_t pca9685_bus_create(void)
{
    if (s_bus) {
        return ESP_OK;
    }

    const i2c_master_bus_config_t bus_cfg = {
        .i2c_port = HW_ORACLE_I2C_PORT,
        .sda_io_num = HW_ORACLE_I2C_SDA,
        .scl_io_num = HW_ORACLE_I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 4,
        .flags = {.enable_internal_pullup = true},
    };

    return i2c_new_master_bus(&bus_cfg, &s_bus);
}

bool pca9685_probe(void)
{
    if (HW_ORACLE_I2C_SDA == GPIO_NUM_NC || HW_ORACLE_I2C_SCL == GPIO_NUM_NC) {
        return false;
    }
    if (pca9685_bus_create() != ESP_OK) {
        return false;
    }

    i2c_master_dev_handle_t probe_dev;
    const i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = HW_PCA9685_ADDR,
        .scl_speed_hz = 100000,
    };

    esp_err_t err = i2c_master_bus_add_device(s_bus, &dev_cfg, &probe_dev);
    if (err != ESP_OK) {
        return false;
    }
    i2c_master_bus_rm_device(probe_dev);
    return true;
}

esp_err_t pca9685_init(void)
{
    if (s_inited) {
        return ESP_OK;
    }

    esp_err_t err = pca9685_bus_create();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "i2c bus: %s", esp_err_to_name(err));
        return err;
    }

    const i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = HW_PCA9685_ADDR,
        .scl_speed_hz = 100000,
        .scl_wait_us = 0,
        .flags = {.disable_ack_check = 0},
    };

    err = i2c_master_bus_add_device(s_bus, &dev_cfg, &s_dev);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "add_device: %s", esp_err_to_name(err));
        return err;
    }

    s_inited = true;
    ESP_LOGI(TAG, "init ok (addr 0x%02x)", HW_PCA9685_ADDR);
    return ESP_OK;
}

void pca9685_deinit(void)
{
    if (!s_inited) {
        return;
    }
    if (s_dev) {
        i2c_master_bus_rm_device(s_dev);
        s_dev = NULL;
    }
    if (s_bus) {
        i2c_del_master_bus(s_bus);
        s_bus = NULL;
    }
    s_inited = false;
}
