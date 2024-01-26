#include "../include/i2c.h"

void default_i2c_init(){

    i2c_init(i2c_default, 400 * 1000);

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);

    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    printf("I2C init done.\n");
}

I2C_STATE_T default_i2c_reg_write( 
                    const uint addr, 
                    const uint8_t reg, 
                    uint8_t *buf,
                    const uint8_t nbytes) {
    
    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    uint8_t num_bytes_written = 0;
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return i2c_state;
    }

    // Append register address to front of data packet
    msg[0] = reg;
    for (uint8_t i = 0; i < nbytes; i++) {
        msg[i + 1] = buf[i];
    }

    // Write data to register(s) over I2C
    num_bytes_written = i2c_write_blocking(i2c_default, addr, msg, (nbytes + 1), false);

    if(num_bytes_written == nbytes) i2c_state = I2C_ALL_GOOD;

    return i2c_state;
}

I2C_STATE_T default_i2c_reg_read( 
                    const uint addr, 
                    const uint8_t reg, 
                    uint8_t *buf,
                    const uint8_t nbytes) {

    I2C_STATE_T i2c_state = I2C_READ_ERROR;

    uint8_t num_bytes_written = 0;
    uint8_t num_bytes_read = 0;

    // Check to make sure caller is asking for 1 or more bytes
    if (nbytes < 1) {
        return i2c_state;
    }

    num_bytes_written = i2c_write_blocking(i2c_default, addr, &reg, 1, true);
    num_bytes_read = i2c_read_blocking(i2c_default, addr, buf, nbytes, false);

    if(num_bytes_read == nbytes) i2c_state = I2C_ALL_GOOD;

    return i2c_state;
}
