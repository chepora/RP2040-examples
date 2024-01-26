#ifndef BNO055_H__
#define BNO055_H_

#include <stdint.h>
#include <stdio.h>

#include "i2c.h"

#include "pico/stdlib.h"

/* ------------------------------------------------------------ *
 * Bosch BNO0555 I2C ADDRESS                                    *
 * ------------------------------------------------------------ */

#define BNO055_ADDR             0x28

/* ------------------------------------------------------------ *
 * Bosch BNO0555 Chip ID                                        *
 * ------------------------------------------------------------ */

#define BNO055_CHIP_ID          0xA0

/* ------------------------------------------------------------ *
 * Bosch BNO0555 Registers                                      *
 * ------------------------------------------------------------ */

#define BNO055_CHIP_ID_ADDR     0x00
#define BNO055_MODE_IMU         0x08

/* Page ID register, for page switching */
#define BNO055_PAGE_ID_ADDR     0x07

#define BNO055_OPR_MODE_ADDR    0x3D
#define BNO055_PWR_MODE_ADDR    0x3E

#define BNO055_CALIB_STAT_ADDR  0x35
#define BNO055_STEST_RSLT_ADDR  0x34

#define BNO055_SYS_TRIGGER_ADDR 0x3F
#define BNO055_SYS_ERROR_ADDR   0x3A

#define BNO055_TEMP_SOURCE_ADDR 0x40

/* Euler data registers */
#define BNO055_EULER_H_LSB_ADDR      0x1A
#define BNO055_EULER_H_MSB_ADDR      0x1B
#define BNO055_EULER_R_LSB_ADDR      0x1C
#define BNO055_EULER_R_MSB_ADDR      0x1D
#define BNO055_EULER_P_LSB_ADDR      0x1E
#define BNO055_EULER_P_MSB_ADDR      0x1F

/* Acc data registers */
#define BNO055_ACC_DATA_X_LSB_ADDR     0x08
#define BNO055_ACC_DATA_X_MSB_ADDR     0x09
#define BNO055_ACC_DATA_Y_LSB_ADDR     0x0A
#define BNO055_ACC_DATA_Y_MSB_ADDR     0x0B
#define BNO055_ACC_DATA_Z_LSB_ADDR     0x0C
#define BNO055_ACC_DATA_Z_MSB_ADDR     0x0D

/* Mag data registers */
#define BNO055_MAG_DATA_X_LSB_ADDR     0x0E
#define BNO055_MAG_DATA_X_MSB_ADDR     0x0F
#define BNO055_MAG_DATA_Y_LSB_ADDR     0x10
#define BNO055_MAG_DATA_Y_MSB_ADDR     0x11
#define BNO055_MAG_DATA_Z_LSB_ADDR     0x12
#define BNO055_MAG_DATA_Z_MSB_ADDR     0x13

/* Gyro data registers */
#define BNO055_GYRO_DATA_X_LSB_ADDR     0x14
#define BNO055_GYRO_DATA_X_MSB_ADDR     0x15
#define BNO055_GYRO_DATA_Y_LSB_ADDR     0x16
#define BNO055_GYRO_DATA_Y_MSB_ADDR     0x17
#define BNO055_GYRO_DATA_Z_LSB_ADDR     0x18
#define BNO055_GYRO_DATA_Z_MSB_ADDR     0x19

/* Registers to set Gyrosscope Any Motion Interrupt */
/* Interrupt registers*/
#define BNO055_INT_MASK_ADDR                0X0F
#define BNO055_INT_ADDR                     0X10
#define BNO055_GYRO_INTR_SETING_ADDR        0X17
#define BNO055_GYRO_ANY_MOTION_THRES_ADDR   0X1E
#define BNO055_GYRO_ANY_MOTION_SET_ADDR     0X1F

/*Interrupt status registers*/
#define BNO055_INTR_STAT_GYRO_ANY_MOTION_POS      2
#define BNO055_INTR_STAT_GYRO_ANY_MOTION_MSK      0X04
#define BNO055_INTR_STAT_GYRO_ANY_MOTION_LEN      1
// #define BNO055_INTR_STAT_GYRO_ANY_MOTION_REG      BNO055_INTR_STAT_ADDR

/* Axis mapping registers and value for remap P0*/
#define BNO055_AXIS_REMAP_CONFIG_ADDR     0x41
#define BNO055_AXIS_REMAP_SIGN_ADDR       0x42
#define BNO055_AXIS_CONFIG                0x21
#define BNO055_AXIS_SIGN                  0x04

typedef struct BNO055_VAR {

    uint8_t BNO055_addr;
    uint8_t id_reg_addr;

} BNO055_VAR;

typedef enum {
    BNO055_ALL_GOOD    = 0x00,
    BNO055_WRITE_ERROR = 0x0F,
    BNO055_READ_ERROR  = 0xF0,
} BNO055_STATE_T;

typedef enum {
   config   = 0x00,
   /* Non-Fusion Modes */
   acconly  = 0x01,
   magonly  = 0x02,
   gyronly  = 0x03,
   accmag   = 0x04,
   accgyro  = 0x05,
   maggyro  = 0x06,
   amg      = 0x07,
   /* Fusion Modes */
   imu      = 0x08,
   compass  = 0x09,
   m4g      = 0x0A,
   ndof     = 0x0B,
   ndof_fmc = 0x0C
} operation_mode_t;

typedef enum {
   normal  = 0x00,
   low     = 0x01,
   suspend = 0x02
} power_mode_t;

typedef enum {

    axis_remap_P0 = 0x21,
    axis_remap_P1 = 0x24,
    axis_remap_P2 = 0x24,
    axis_remap_P3 = 0x21,
    axis_remap_P4 = 0x24,
    axis_remap_P5 = 0x21,
    axis_remap_P6 = 0x21,
    axis_remap_P7 = 0x24,

} axis_remap_t;

typedef enum {

    axis_sign_P0 = 0x04,
    axis_sign_P1 = 0x00,
    axis_sign_P2 = 0x06,
    axis_sign_P3 = 0x02,
    axis_sign_P4 = 0x03,
    axis_sign_P5 = 0x01,
    axis_sign_P6 = 0x07,
    axis_sign_P7 = 0x05,

} axis_sign_t;

typedef struct axis_placement {

    axis_remap_t    axis_remap;
    axis_sign_t     axis_sign;

} axis_placement_t ;


typedef struct {
   double eul_head;
   double eul_roll;
   double eul_pitch;
} euler_angles_t;

void BNO055_init();
void BNO055_test();

BNO055_STATE_T BNO055_get_device_id();

BNO055_STATE_T BNO055_set_reg_page(uint8_t page);

BNO055_STATE_T BNO055_set_to_config_mode();
BNO055_STATE_T BNO055_print_operation_mode();
BNO055_STATE_T BNO055_set_operation_mode(operation_mode_t newmode);

BNO055_STATE_T BNO055_set_power_mode(power_mode_t newmode);

BNO055_STATE_T BNO055_get_calib_status();
BNO055_STATE_T BNO055_start_selftest();
BNO055_STATE_T BNO055_selftest_results();

BNO055_STATE_T BNO055_get_axis_mode(BNO055_VAR* ptBNO055_var);
BNO055_STATE_T BNO055_set_axis_mode(axis_placement_t req_axis_placement);

BNO055_STATE_T BNO055_print_eul(euler_angles_t* ptEulAngles);

BNO055_STATE_T BNO055_get_acc_xyz();

BNO055_STATE_T BNO055_get_mag_xyz();

BNO055_STATE_T BNO055_get_gyro_xyz();

#endif