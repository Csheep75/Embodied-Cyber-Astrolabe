#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool pca9685_probe(void);
esp_err_t pca9685_init(void);
void pca9685_deinit(void);

#ifdef __cplusplus
}
#endif
