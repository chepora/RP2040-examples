set(SRC_FILES timer.c
              ./include/timer.h
        )

add_library(timer ${SRC_FILES})


target_link_libraries(timer pico_stdlib)
target_include_directories(timer PUBLIC ./include/)
