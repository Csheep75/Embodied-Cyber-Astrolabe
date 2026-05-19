#pragma once

/**
 * 统一引脚表：两块板烧录同一固件，上电自动识别角色。
 * WROOM 载板 / EYE 本体 接线见 docs/WIRING.md
 */
#define HW_CONFIG_VERSION "2026-05-19-unified"

#include "driver/i2c_types.h"
#include "hal/gpio_types.h"

/* 角色识别：WROOM 载板将 STRAP 接 GND；EYE 悬空(内部上拉)= 喵本体 */
#define HW_BOARD_STRAP_GPIO    GPIO_NUM_48
#define HW_BOARD_STRAP_ORACLE_LEVEL  0

/* ── Oracle / WROOM 载板 (转盘、舵机、步进、霍尔) ── */
#define HW_ORACLE_I2C_PORT     I2C_NUM_0
#define HW_ORACLE_I2C_SDA      GPIO_NUM_8
#define HW_ORACLE_I2C_SCL      GPIO_NUM_9
#define HW_PCA9685_ADDR        0x40

#define HW_HALL_GPIO           GPIO_NUM_4
#define HW_STEPPER_IN1         GPIO_NUM_14
#define HW_STEPPER_IN2         GPIO_NUM_26
#define HW_STEPPER_IN3         GPIO_NUM_27
#define HW_STEPPER_IN4         GPIO_NUM_33
#define HW_BIG_SERVO_PCA_CH    8

/* 兼容旧宏名 */
#define HW_I2C_PORT            HW_ORACLE_I2C_PORT
#define HW_I2C_SDA_GPIO        HW_ORACLE_I2C_SDA
#define HW_I2C_SCL_GPIO        HW_ORACLE_I2C_SCL

/* ── Cat / EYE 本体 (外扩，待接线后修改) ── */
#define HW_CAT_I2C_PORT        I2C_NUM_0
#define HW_CAT_I2C_SDA         GPIO_NUM_NC
#define HW_CAT_I2C_SCL         GPIO_NUM_NC
#define HW_TOUCH_GPIO          GPIO_NUM_NC
#define HW_WS2812_GPIO         GPIO_NUM_NC
