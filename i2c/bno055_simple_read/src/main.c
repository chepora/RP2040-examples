#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define PICO_DEFAULT_I2C 1

/* On Adafruit Feather RP2040 one I2C can be used via Stemma QT(JST SH)*/
/* this is the second I2C, I2C 1 on GPIO 2(SCL_1) and GPIO 3(SDA_1)*/

static const uint8_t BNO055_ADDR        = 0x28;
static const uint8_t BNO055_ID_REG_ADDR = 0x00;
static const uint8_t BNO055_DEVICE_ID   = 0xA0;


#define I2C_INST i2c1
#define I2C_SDA  2
#define I2C_SCL  3

/*******************************************************************************
 * Function Declarations
 */
int reg_write(i2c_inst_t *i2c, 
                const uint addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes);

int reg_read(   i2c_inst_t *i2c,
                const uint addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes);

/*******************************************************************************
 * Function Definitions
 */

// Write 1 byte to the specified register
int reg_write(  i2c_inst_t *i2c, 
                const uint addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Append register address to front of data packet
    msg[0] = reg;
    for (int i = 0; i < nbytes; i++) {
        msg[i + 1] = buf[i];
    }

    // Write data to register(s) over I2C
    i2c_write_blocking(i2c, addr, msg, (nbytes + 1), false);

    return num_bytes_read;
}

// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
int reg_read(  i2c_inst_t *i2c,
                const uint addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;

    // Check to make sure caller is asking for 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Read data from register(s) over I2C
    i2c_write_blocking(i2c, addr, &reg, 1, true);
    num_bytes_read = i2c_read_blocking(i2c, addr, buf, nbytes, false);

    return num_bytes_read;
}

/*******************************************************************************
 * Main
 */
int main() {

    bool is_available = false;
    
    // Buffer to store raw reads
    uint8_t data[6];

    // Ports
    i2c_inst_t *i2c = i2c1;

    // Pins
    const uint sda_pin = 3;
    const uint scl_pin = 2;

    int num_bytes_read = 0;

    stdio_init_all();

    //Initialize I2C port at 400 kHz
    i2c_init(i2c, 400 * 1000);

    // Initialize I2C pins
    gpio_set_function(sda_pin,GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin );

    gpio_set_function(scl_pin,GPIO_FUNC_I2C);
    gpio_pull_up(scl_pin);


    sleep_ms(650);

    printf("Trying to communicate with BNO055\r\n");

    // Read device ID to make sure that we can communicate with the device

    // Read data from register(s) over I2C
    i2c_write_blocking(i2c, BNO055_ADDR, &BNO055_ID_REG_ADDR, 1, true);
    num_bytes_read = i2c_read_blocking(i2c, BNO055_ADDR, data, 1, false);
    //reg_read(I2C_INST, BNO055_ADDR, BNO055_ID_REG_ADDR, data, 1);
    if (data[0] != BNO055_DEVICE_ID) {
        printf("ERROR: Could not communicate with BNO055\r\n");
        printf("Data read: %x\r\n", data[0]);
        while(1)
    }else{
        printf("Found device with device id %x\n", BNO055_DEVICE_ID);
    }

    sleep_ms(500);

    // set orientation mode -> manual p.27

    // set operating mode -> maual 3.3 ff

    while(1){

        // get euler angles


    }    
}



