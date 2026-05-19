#include "demo_console.h"

#include "board_role.h"
#include "cat_state_machine.h"
#include "demo_mode.h"
#include "oracle_state_machine.h"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "demo_console";

static void demo_console_task(void *arg)
{
    (void)arg;
    char line[64];

    ESP_LOGI(TAG, "串口命令: mode idle|pet|bristle|tail|spin | role | help");
    while (true) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            vTaskDelay(pdMS_TO_TICKS(200));
            continue;
        }
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        if (len == 0) {
            continue;
        }

        if (strcmp(line, "help") == 0) {
            ESP_LOGI(TAG, "mode idle|pet|bristle|tail|spin  role  help");
        } else if (strcmp(line, "role") == 0) {
            ESP_LOGI(TAG, "board=%s demo=%d", board_role_name(board_role_get()),
                     (int)demo_mode_get());
        } else if (strncmp(line, "mode ", 5) == 0) {
            const char *m = line + 5;
            demo_mode_t mode = DEMO_MODE_IDLE;
            if (strcmp(m, "idle") == 0) {
                mode = DEMO_MODE_IDLE;
            } else if (strcmp(m, "pet") == 0) {
                mode = DEMO_MODE_PET_HEAD;
            } else if (strcmp(m, "bristle") == 0) {
                mode = DEMO_MODE_SURPRISE_BRISTLE;
            } else if (strcmp(m, "tail") == 0) {
                mode = DEMO_MODE_TAIL_PROTEST;
            } else if (strcmp(m, "spin") == 0) {
                mode = DEMO_MODE_TURNTABLE_SPIN;
            } else {
                ESP_LOGW(TAG, "unknown mode: %s", m);
                continue;
            }
            demo_mode_set(mode, true);
            if (board_role_get() == BOARD_ROLE_CAT) {
                cat_state_machine_on_demo_mode(mode);
            } else {
                oracle_state_machine_on_demo_mode(mode);
            }
        } else {
            ESP_LOGW(TAG, "unknown: %s", line);
        }
    }
}

void demo_console_start(void)
{
    xTaskCreate(demo_console_task, "demo_console", 4096, NULL, 5, NULL);
}
