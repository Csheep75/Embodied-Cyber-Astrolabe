#pragma once

#include "demo_mode.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t comm_espnow_init(void);
esp_err_t comm_espnow_send_demo_mode(demo_mode_t mode);

#ifdef __cplusplus
}
#endif
