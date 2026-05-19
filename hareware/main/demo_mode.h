#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DEMO_MODE_IDLE = 0,
    DEMO_MODE_PET_HEAD,
    DEMO_MODE_SURPRISE_BRISTLE,
    DEMO_MODE_TAIL_PROTEST,
    DEMO_MODE_TURNTABLE_SPIN,
    DEMO_MODE_MAX,
} demo_mode_t;

esp_err_t demo_mode_init(void);

demo_mode_t demo_mode_get(void);

/** broadcast_peer: 通过 ESP-NOW 同步到另一块板 */
esp_err_t demo_mode_set(demo_mode_t mode, bool broadcast_peer);

#ifdef __cplusplus
}
#endif
