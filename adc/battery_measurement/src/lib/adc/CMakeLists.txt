
set(SRC_FILES adc.c
              ./include/adc.h
        )

add_library(adc ${SRC_FILES})

target_link_libraries(adc pico_stdlib hardware_gpio hardware_adc)
target_include_directories(adc PUBLIC ./include/)
