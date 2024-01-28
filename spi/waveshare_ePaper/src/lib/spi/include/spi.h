#ifndef SPI_H__
#define SPI_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

typedef struct {

    uint8_t spi_sck_pin;    // SCK serial clock
    uint8_t spi_tx_pin;     // SDO serial data out -> DIN on waveshare
    uint8_t spi_cs_pin;     // CS chipselect 
    uint8_t spi_rx_pin;     // data/command - DC
    uint8_t spi_rs_pin;     // reset
    uint8_t spi_busy_pin;   // 


} spi_params_t;

typedef enum {
    SPI_ALL_GOOD    = 0x00,
    SPI_WRITE_ERROR = 0x0F,
    SPI_READ_ERROR  = 0xF0,
} spi_state_e;

void local_spi_init(spi_params_t* pt_spi_params);
spi_state_e spi_write(const uint8_t *src, size_t len);

#endif