set(SRC_FILES pio.c
              ./include/pio.h
        )

add_library(pio ${SRC_FILES})
pico_generate_pio_header(pio ${CMAKE_CURRENT_LIST_DIR}/pio_poc.pio)

target_link_libraries(pio pico_stdlib hardware_pio hardware_clocks)
target_include_directories(pio PUBLIC ./include/)
