idf_component_register(
    SRCS "stepper_28byj.c"
    INCLUDE_DIRS "."
    REQUIRES esp_driver_gpio shared
)
