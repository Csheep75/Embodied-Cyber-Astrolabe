#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BOARD_ROLE_UNKNOWN = 0,
    BOARD_ROLE_ORACLE,
    BOARD_ROLE_CAT,
} board_role_t;

board_role_t board_role_detect(void);

board_role_t board_role_get(void);

const char *board_role_name(board_role_t role);

#ifdef __cplusplus
}
#endif
