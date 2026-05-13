#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t hall_sensor_init(void);
bool hall_sensor_is_triggered(void);

#ifdef __cplusplus
}
#endif
