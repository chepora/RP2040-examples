#include "../include/pio.h"

// Our assembled program:
#include "pio_poc.pio.h"

#define BRIGTNESS 0.01

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r * BRIGTNESS) << 8) |
            ((uint32_t) (g * BRIGTNESS) << 16) |
            (uint32_t) (b * BRIGTNESS);
}

void pio_init() {
    //set_sys_clock_48();
    stdio_init_all();
    printf("WS2812 Smoke Test, using pin %d", PICO_DEFAULT_WS2812_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, PICO_DEFAULT_WS2812_PIN, 800000, true);

    while (1) {

        put_pixel(urgb_u32(0xff, 0, 0));
        sleep_ms(500);
        put_pixel(urgb_u32(0, 0xff, 0));
        sleep_ms(500);
        put_pixel(urgb_u32(0, 0, 0xff));
        sleep_ms(500);
    }
}

