#pragma once

#include "driver/i2c_types.h"
#include "hal/gpio_types.h"

#define HW_I2C_PORT        I2C_NUM_0
#define HW_I2C_SDA_GPIO    21
#define HW_I2C_SCL_GPIO    22
#define HW_PCA9685_ADDR    0x40

#define HW_HALL_GPIO       GPIO_NUM_4

#define HW_STEPPER_IN1     GPIO_NUM_25
#define HW_STEPPER_IN2     GPIO_NUM_26
#define HW_STEPPER_IN3     GPIO_NUM_27
#define HW_STEPPER_IN4     GPIO_NUM_33
