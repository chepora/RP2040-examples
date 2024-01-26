#ifndef I2C_H__
#define I2C_H_

#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef enum {
    I2C_ALL_GOOD    = 0x00,
    I2C_WRITE_ERROR = 0x0F,
    I2C_READ_ERROR  = 0xF0,
} I2C_STATE_T;

void default_i2c_init();

I2C_STATE_T default_i2c_reg_write( 
                    const uint addr, 
                    const uint8_t reg, 
                    uint8_t *buf,
                    const uint8_t nbytes);

I2C_STATE_T default_i2c_reg_read(
                    const uint addr, 
                    const uint8_t reg, 
                    uint8_t *buf,
                    const uint8_t nbytes);

#endif