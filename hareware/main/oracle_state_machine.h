#pragma once

#include "demo_mode.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t oracle_state_machine_init(void);
void oracle_state_machine_on_demo_mode(demo_mode_t mode);

#ifdef __cplusplus
}
#endif
