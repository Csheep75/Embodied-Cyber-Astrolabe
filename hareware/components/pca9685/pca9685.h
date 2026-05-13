#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t pca9685_init(void);
void pca9685_deinit(void);

#ifdef __cplusplus
}
#endif
