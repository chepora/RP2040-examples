
set(SRC_FILES bno055.c
              ./include/bno055.h
        )

add_library(bno055 ${SRC_FILES})

target_link_libraries(bno055 pico_stdlib hardware_i2c i2c)
target_include_directories(bno055 PUBLIC ./include/)
