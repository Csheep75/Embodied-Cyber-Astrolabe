idf_component_register(
    SRCS "pca9685.c"
    INCLUDE_DIRS "."
    REQUIRES esp_driver_i2c shared
)
