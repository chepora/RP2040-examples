set(SRC_FILES button.c
              ./include/button.h
        )

add_library(button ${SRC_FILES})

target_link_libraries(button pico_stdlib hardware_gpio)
target_include_directories(button PUBLIC ./include/)
