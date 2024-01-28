#ifndef EPAPER_H__
#define EPAPER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "spi.h"
#include "ImageData.h"

typedef struct {

    uint8_t* pt_image;
    uint16_t pic_width;
    uint16_t pic_height;
    uint16_t pic_width_memory;
    uint16_t pic_height_memory;
    uint16_t pic_color;
    uint16_t pic_rotate;
    uint16_t pic_mirror;
    uint16_t pic_width_byte;
    uint16_t pic_height_byte;
    uint16_t pic_scale;
} epaper_picture_t;

typedef struct {

    spi_params_t spi_params;

    uint8_t x_start; //EPD_1IN54_V2_HEIGHT-1,
    uint8_t x_end;
    uint8_t y_start; //EPD_1IN54_V2_WIDTH-1
    uint8_t y_end;

    int16_t imagesize;

    epaper_picture_t epaper_picture;

} epaper_params_t;

typedef enum {

    EPAPER_ALL_GOOD             = 0x00,
    EPAPER_INIT_ERROR           = 0x01,
    EPAPER_DEV_BUSY             = 0x02,
    EPAPER_SPI_WRITE_ERROR      = 0x04,
    EPAPER_SPI_READ_ERROR       = 0x08,
    EPAPER_GPIO_WRITE_ERROR     = 0x0F,
    EPAPER_GPIO_READ_ERROR      = 0x10,

} epaper_status_e;

epaper_status_e epaper_init(epaper_params_t* pt_epaper_params);
epaper_status_e epaper_display_init(epaper_params_t* pt_epaper_params);
epaper_status_e epaper_clear_display(epaper_params_t* pt_epaper_params);
epaper_status_e epaper_paint_color(epaper_params_t* pt_epaper_params);
epaper_status_e epaper_draw_bitmap(epaper_params_t* pt_epaper_params, const unsigned char* image_buffer);
epaper_status_e epaper_send_to_display(epaper_params_t* pt_epaper_params);

#endif