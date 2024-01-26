#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bno055.h"
#include "pico/stdlib.h"


/* On Adafruit Feather RP2040 one I2C can be used via Stemma QT(JST SH)*/
/* this is the second I2C, I2C 1 on GPIO 2(SCL_1) and GPIO 3(SDA_1)*/


int main() {

    stdio_init_all();

    BNO055_init();
    BNO055_test();

}
