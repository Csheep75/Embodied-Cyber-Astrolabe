#pragma once

#include "esp_log.h"

#ifndef APP_LOG_TAG
#define APP_LOG_TAG "app"
#endif

#define APP_LOGI(fmt, ...) ESP_LOGI(APP_LOG_TAG, fmt, ##__VA_ARGS__)
#define APP_LOGW(fmt, ...) ESP_LOGW(APP_LOG_TAG, fmt, ##__VA_ARGS__)
#define APP_LOGE(fmt, ...) ESP_LOGE(APP_LOG_TAG, fmt, ##__VA_ARGS__)
