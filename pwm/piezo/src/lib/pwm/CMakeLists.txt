set(SRC_FILES pwm.c
              ./include/pwm.h
        )

add_library(pwm ${SRC_FILES})

target_link_libraries(pwm pico_stdlib hardware_gpio hardware_pwm hardware_clocks)
target_include_directories(pwm PUBLIC ./include/)
