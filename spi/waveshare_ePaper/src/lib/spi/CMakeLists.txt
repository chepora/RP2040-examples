set(SRC_FILES spi.c
              ./include/spi.h
        )

add_library(spi ${SRC_FILES})

target_link_libraries(spi pico_stdlib hardware_gpio hardware_spi)
target_include_directories(spi PUBLIC ./include/)
