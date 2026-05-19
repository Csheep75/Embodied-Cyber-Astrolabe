idf_component_register(
    SRCS "hall_sensor.c"
    INCLUDE_DIRS "."
    REQUIRES esp_driver_gpio shared
)
