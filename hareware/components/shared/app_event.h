#pragma once

#include <stdint.h>

typedef enum {
    APP_EVENT_NONE = 0,
} app_event_id_t;

typedef struct {
    app_event_id_t id;
    uint32_t arg;
} app_event_t;
