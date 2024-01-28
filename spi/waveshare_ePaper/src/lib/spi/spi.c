#include "../include/spi.h"

#define READ_BIT 0x80
#define PIN_CS   9

static void read_registers(uint8_t reg, uint8_t *buf, uint16_t len);

static inline void cs_select();
static inline void cs_deselect();

void local_spi_init(spi_params_t* pt_spi_params){

    // nptr check missing 

    gpio_set_dir(pt_spi_params->spi_cs_pin, GPIO_OUT);
    gpio_set_dir(pt_spi_params->spi_rx_pin, GPIO_OUT);
    gpio_set_dir(pt_spi_params->spi_rs_pin, GPIO_OUT);
    gpio_set_dir(pt_spi_params->spi_busy_pin, GPIO_IN);

    // sett cs high
    gpio_put(pt_spi_params->spi_cs_pin, 1);

    spi_init(spi1, 4000 * 1000);

    gpio_set_function(pt_spi_params->spi_sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(pt_spi_params->spi_tx_pin, GPIO_FUNC_SPI);


    printf("SPI init done.\n");
}

spi_state_e spi_write(const uint8_t* data, size_t len){

    spi_state_e spi_state =  SPI_WRITE_ERROR;
    size_t bytes_written = 0;

    bytes_written = spi_write_blocking(spi1, data, len);

    if (bytes_written == len)
    {
        spi_state =  SPI_ALL_GOOD;
    }else
    {
        printf("SPI Error: bytes written %d vs. req. len %d \n", bytes_written, len);
    }
    
    return spi_state;
}