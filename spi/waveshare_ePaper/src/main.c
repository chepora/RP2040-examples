#include <stdio.h>

#include "epaper.h"


int main() {

    epaper_status_e epaper_status = EPAPER_INIT_ERROR;

    stdio_init_all(); // UART setup for both input and output

    epaper_params_t* pt_epaper_params = (epaper_params_t*) malloc(sizeof(epaper_params_t));
    
    pt_epaper_params->spi_params.spi_sck_pin    = 10;
    pt_epaper_params->spi_params.spi_tx_pin     = 11;
    pt_epaper_params->spi_params.spi_cs_pin     =  9;
    pt_epaper_params->spi_params.spi_rx_pin     =  8;
    pt_epaper_params->spi_params.spi_rs_pin     = 12;
    pt_epaper_params->spi_params.spi_busy_pin   = 13;

    epaper_status = epaper_init(pt_epaper_params);

    // create a new image
    uint8_t* blackimage;
    blackimage = (uint8_t *)malloc((pt_epaper_params->imagesize));

    pt_epaper_params->epaper_picture.pt_image = blackimage;

    epaper_status = epaper_paint_color(pt_epaper_params);

    pt_epaper_params->epaper_picture.pic_color = 0x00;

    epaper_status = epaper_paint_color(pt_epaper_params);
    
    epaper_status = epaper_draw_bitmap(pt_epaper_params, turtle);

    epaper_status = epaper_send_to_display(pt_epaper_params);
}



