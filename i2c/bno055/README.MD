# First steps with the BNO055

Connecting to the [BNO055](https://www.bosch-sensortec.com/products/smart-sensor-systems/bno055/) via I2C.

Triggering selftests and reading some values.

All is output to UART serial.

## Configuring the environment

This was built and depends on the [RPi Pico SDK V1.5.1](https://github.com/raspberrypi/pico-sdk)

Its location must be set as an environment, e.g.:

```shell
export PICO_SDK_PATH="your_local_path"
```

The project is configured for the Adafruit Feather RP2040.
To change this, please change the follwing line `./CMakeLists.txt` in the projects root directory.

```cmake
set(PICO_BOARD "adafruit_feather_rp2040")
```
And `PICO_BOARD=adafruit_feather_rp2040` in `./build.sh`

Add a `./build` folder and run `cmake ..` from inside it.

## Building and flashing

Run `./build.sh`

If you are using [picotool](https://github.com/raspberrypi/picotool) you can simple flash in two steps:

1. Bring the board into BOOTSEL mode by holding the the same called button while resetting
2. Write the built `.uf2` onto the board with the following command:
    ```shell
    "PATH_TO_PICOTOOL/picotool load .build/debug/src/console_poc.uf2
    ```