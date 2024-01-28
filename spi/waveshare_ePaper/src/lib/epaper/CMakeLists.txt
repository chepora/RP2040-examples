set(SRC_FILES epaper.c
            ImageData.c
            ./include/epaper.h
            ./include/ImageData.h
        )

add_library(epaper ${SRC_FILES})

target_link_libraries(epaper pico_stdlib spi)
target_include_directories(epaper PUBLIC ./include/)
