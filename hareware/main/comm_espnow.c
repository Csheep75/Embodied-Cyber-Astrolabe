#include "comm_espnow.h"

#include "board_role.h"
#include "cat_state_machine.h"
#include "demo_mode.h"
#include "oracle_state_machine.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_now.h"
#include "esp_wifi.h"

#include <string.h>

static const char *TAG = "espnow";

#define ESPNOW_MAGIC 0xA5
#define ESPNOW_CMD_DEMO_MODE 0x01

typedef struct __attribute__((packed)) {
    uint8_t magic;
    uint8_t cmd;
    uint8_t demo_mode;
    uint8_t sender_role;
} espnow_demo_pkt_t;

static const uint8_t s_broadcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static bool s_ready;

static void espnow_recv_cb(const esp_now_recv_info_t *info, const uint8_t *data, int len)
{
    (void)info;
    if (len < (int)sizeof(espnow_demo_pkt_t)) {
        return;
    }
    const espnow_demo_pkt_t *pkt = (const espnow_demo_pkt_t *)data;
    if (pkt->magic != ESPNOW_MAGIC || pkt->cmd != ESPNOW_CMD_DEMO_MODE) {
        return;
    }
    if (pkt->demo_mode >= DEMO_MODE_MAX) {
        return;
    }

    demo_mode_t mode = (demo_mode_t)pkt->demo_mode;
    ESP_LOGI(TAG, "peer demo mode %d (from role %u)", (int)mode, pkt->sender_role);
    demo_mode_set(mode, false);

    if (board_role_get() == BOARD_ROLE_CAT) {
        cat_state_machine_on_demo_mode(mode);
    } else {
        oracle_state_machine_on_demo_mode(mode);
    }
}

static esp_err_t espnow_wifi_start(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE));
    return ESP_OK;
}

esp_err_t comm_espnow_init(void)
{
    if (s_ready) {
        return ESP_OK;
    }

    esp_err_t err = espnow_wifi_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "wifi: %s", esp_err_to_name(err));
        return err;
    }

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(espnow_recv_cb));

    esp_now_peer_info_t peer = {0};
    memcpy(peer.peer_addr, s_broadcast_mac, 6);
    peer.channel = 1;
    peer.encrypt = false;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));

    s_ready = true;
    ESP_LOGI(TAG, "init ok (broadcast ch1)");
    return ESP_OK;
}

esp_err_t comm_espnow_send_demo_mode(demo_mode_t mode)
{
    if (!s_ready) {
        return ESP_ERR_INVALID_STATE;
    }

    espnow_demo_pkt_t pkt = {
        .magic = ESPNOW_MAGIC,
        .cmd = ESPNOW_CMD_DEMO_MODE,
        .demo_mode = (uint8_t)mode,
        .sender_role = (uint8_t)board_role_get(),
    };

    esp_err_t err = esp_now_send(s_broadcast_mac, (const uint8_t *)&pkt, sizeof(pkt));
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "send: %s", esp_err_to_name(err));
    }
    return err;
}
