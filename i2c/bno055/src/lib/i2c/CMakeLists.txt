
set(SRC_FILES i2c.c
              ./include/i2c.h
        )

add_library(i2c ${SRC_FILES})

target_link_libraries(i2c pico_stdlib hardware_i2c)
target_include_directories(i2c PUBLIC ./include/)
