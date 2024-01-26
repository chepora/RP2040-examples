#include "../include/bno055.h"


void BNO055_init(){

    // default i2c is defined via board file
    default_i2c_init();
    // Power-on-reset time for the BNO055 is 650 ms. Give it time to start.
    sleep_ms(1650);
}

void BNO055_test(){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    
    // Buffer to store raw reads
    uint8_t data[6];

    axis_placement_t req_axis_placement = {
        .axis_remap = axis_remap_P0,
        .axis_sign = axis_sign_P0,
    };

    euler_angles_t tEulAngles;

    power_mode_t req_power_mode = normal;
    
    // Read device ID to make sure that we can communicate with the device
    i2c_state =  BNO055_get_device_id();

    printf("Setting power mode to NORMAL = 0x00 now.\n");

    i2c_state =  BNO055_set_power_mode(req_power_mode);

    i2c_state =  BNO055_get_calib_status();
    i2c_state =  BNO055_start_selftest();

    i2c_state =  BNO055_print_operation_mode();

    printf("Will try to set to IMU mode = 0x08 now.\n");

    operation_mode_t mode_imu = imu;

    i2c_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    i2c_state =  BNO055_print_operation_mode();

    printf("Will try to set to axis placement P0 now.\n");

    i2c_state = BNO055_set_axis_mode(req_axis_placement);

    i2c_state = BNO055_print_eul(&tEulAngles);

    mode_imu = acconly;

    printf("Will try to set to ACCONLY mode = 0x02 now.\n");

    i2c_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    i2c_state =  BNO055_print_operation_mode();

    i2c_state = BNO055_get_acc_xyz();

    mode_imu = magonly;

    printf("Will try to set to MAGONLY mode = 0x02 now.\n");

    i2c_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    i2c_state =  BNO055_print_operation_mode();

    i2c_state = BNO055_get_mag_xyz();

    mode_imu = gyronly;

    printf("Will try to set to GYRONLY mode = 0x03 now.\n");

    i2c_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    i2c_state =  BNO055_print_operation_mode();

    i2c_state = BNO055_get_gyro_xyz();

    mode_imu = amg;

    printf("Will try to set to AMG mode = 0x07 now.\n");

    i2c_state = BNO055_set_operation_mode(mode_imu);

    printf("Reading operation mode again.\n");

    i2c_state =  BNO055_print_operation_mode();

    i2c_state = BNO055_get_acc_xyz();
    i2c_state = BNO055_get_mag_xyz();
    i2c_state = BNO055_get_gyro_xyz();


}

BNO055_STATE_T BNO055_get_device_id(){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    
    // Buffer to store raw reads
    uint8_t data[6];
    
    // Read device ID to make sure that we can communicate with the device
    i2c_state =  default_i2c_reg_read(BNO055_ADDR, BNO055_CHIP_ID_ADDR, data, 1);

    if (data[0] != BNO055_CHIP_ID) {
        printf("ERROR: Could not communicate with BNO055\r\n");
        printf("Data read: %x\r\n", data[0]);
    }else{
        printf("Found device with device id %x\n", BNO055_CHIP_ID);

    }

    return i2c_state;
}

BNO055_STATE_T BNO055_set_reg_page(uint8_t page){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_PAGE_ID_ADDR, &page, 1);

    return i2c_state;

}

BNO055_STATE_T BNO055_set_to_config_mode(){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    uint8_t  page   = 0;
    i2c_state       = BNO055_set_reg_page(page);

    // set to configuration mode
    operation_mode_t config_mode = config;
    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_OPR_MODE_ADDR, &config_mode, 1);
    /* --------------------------------------------------------- *
    * switch time: any->config needs 7ms + small buffer = 10ms  *
    * --------------------------------------------------------- */
    sleep_ms(10);

    return i2c_state;
}

BNO055_STATE_T BNO055_print_operation_mode(){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    uint8_t operation_mode = 0;
    uint8_t data[6];
    
    // read operation mode
    i2c_state =  default_i2c_reg_read(BNO055_ADDR, BNO055_OPR_MODE_ADDR, data, 1);

    // operation mode lies in the 4 lower bits
    operation_mode = data[0] & 0x0F;

    if (i2c_state != I2C_ALL_GOOD) {
        printf("ERROR: Could not communicate with BNO055\r\n");
        printf("i2c_state returned: %x\r\n", i2c_state);
    }else{
        printf("BNO055_get_operation_mode returned %x\n", operation_mode);
    }
}

BNO055_STATE_T BNO055_set_operation_mode(operation_mode_t newmode){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    // set to configuration mode
    i2c_state = BNO055_set_to_config_mode();

    // set requested mode
    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_OPR_MODE_ADDR, &newmode, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return i2c_state;
}

BNO055_STATE_T BNO055_set_power_mode(power_mode_t newmode){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    // set to configuration mode
    i2c_state = BNO055_set_to_config_mode();

    // set requested mode
    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_PWR_MODE_ADDR, &newmode, 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return i2c_state;
}

BNO055_STATE_T BNO055_set_axis_mode(axis_placement_t req_axis_placement){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;

    // set to configuration mode
    i2c_state = BNO055_set_to_config_mode();

    // write axis remap for requested placement
    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_AXIS_REMAP_CONFIG_ADDR, &(req_axis_placement.axis_remap), 1);

    // write axis sign for requested placement
    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_AXIS_REMAP_SIGN_ADDR, &(req_axis_placement.axis_remap), 1);
    /* --------------------------------------------------------- *
     * switch time: config->any needs 19ms + small buffer = 25ms *
     * --------------------------------------------------------- */
    sleep_ms(25);

    return i2c_state;
}

BNO055_STATE_T BNO055_print_eul(euler_angles_t* ptEulAngles){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    uint8_t euler_angles_data[6];
    int16_t buffer = 0;

    // to get euler angles sensor needs to be in fusion mode( operation mode > 0x07) !
    // might do mode check here

    // might set unit here

    // defines the angle unit (datasheet p.35)
    // set 16.0 for degrees, 900.0 for rad/s
    float angle_unit = 900.0;                

    // read euler angle data
    i2c_state = default_i2c_reg_read(BNO055_ADDR,  BNO055_EULER_H_LSB_ADDR, euler_angles_data, 6);

    buffer = ((uint16_t)euler_angles_data[1] << 8) | euler_angles_data[0];
    printf("Euler Orientation Heading: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[0], euler_angles_data[1], buffer);
    ptEulAngles->eul_head = (double) buffer / angle_unit;
    printf("Euler Orientation Heading: %f\n", ptEulAngles->eul_head);

    buffer = ((int16_t)euler_angles_data[3] << 8) | euler_angles_data[2];
    printf("Euler Orientation Roll: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[2], euler_angles_data[3], buffer);
    ptEulAngles->eul_roll = (double) buffer / angle_unit;
    printf("Euler Orientation Roll: %f\n", ptEulAngles->eul_roll);

    buffer = ((int16_t)euler_angles_data[5] << 8) | euler_angles_data[4];
    printf("Euler Orientation Pitch: LSB [0x%02X] MSB [0x%02X] INT16 [%d]\n", euler_angles_data[4], euler_angles_data[5], buffer);
    ptEulAngles->eul_pitch = (double) buffer / angle_unit;
    printf("Euler Orientation Pitch: %f\n", ptEulAngles->eul_pitch);

    return i2c_state;

}

BNO055_STATE_T BNO055_get_acc_xyz(){

    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    uint8_t acc_data[2] = {0, 0};
    int16_t acc_buff = 0;

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_X_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    printf("ACC X LSB: 0x%02X\n", acc_data[0]);
    printf("ACC X MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    printf("acc_buff_x: %d\n", acc_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_Y_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    printf("ACC Y LSB: 0x%02X\n", acc_data[0]);
    printf("ACC Y MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    printf("acc_buff_y: %d\n", acc_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_ACC_DATA_Z_LSB_ADDR, acc_data, 2);

    acc_data[0] = ((acc_data[0] & 0xFF) >> 0);
    acc_data[1] = ((acc_data[1] & 0xFF) >> 0);

    printf("ACC Z LSB: 0x%02X\n", acc_data[0]);
    printf("ACC Z MSB: 0x%02X\n", acc_data[1]);

    acc_buff = ((int16_t) ((acc_data[0] << 8)| acc_data[1]));
    
    printf("acc_buff_z: %d\n", acc_buff);

    return i2c_state;
}

BNO055_STATE_T BNO055_get_mag_xyz(){
    
    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    uint8_t mag_data[2] = {0, 0};
    int16_t mag_buff = 0;

    // defines the angle unit (datasheet p.35)
    // set 16.0 for degrees, 900.0 for rad/s
    float angle_unit = 900.0;

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_X_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG X LSB: 0x%02X\n", mag_data[0]);
    printf("MAG X MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_x: %d\n", mag_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_MAG_DATA_Y_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG Y LSB: 0x%02X\n", mag_data[0]);
    printf("MAG Y MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_y: %d\n", mag_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_MAG_DATA_Z_LSB_ADDR, mag_data, 2);

    mag_data[0] = ((mag_data[0] & 0xFF) >> 0);
    mag_data[1] = ((mag_data[1] & 0xFF) >> 0);

    printf("MAG Z LSB: 0x%02X\n", mag_data[0]);
    printf("MAG Z MSB: 0x%02X\n", mag_data[1]);

    mag_buff = ((int16_t) ((mag_data[0] << 8)| mag_data[1]));
    
    printf("mag_buff_z: %d\n", mag_buff);

    return i2c_state;
}

BNO055_STATE_T BNO055_get_gyro_xyz(){
    
    I2C_STATE_T i2c_state = I2C_WRITE_ERROR;
    uint8_t gyro_data[2] = {0, 0};
    int16_t gyro_buff = 0;

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_X_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO X LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO X MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_x: %d\n", gyro_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_Y_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO Y LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO Y MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_y: %d\n", gyro_buff);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_GYRO_DATA_Z_LSB_ADDR, gyro_data, 2);

    gyro_data[0] = ((gyro_data[0] & 0xFF) >> 0);
    gyro_data[1] = ((gyro_data[1] & 0xFF) >> 0);

    printf("GYRO Z LSB: 0x%02X\n", gyro_data[0]);
    printf("GYRO Z MSB: 0x%02X\n", gyro_data[1]);

    gyro_buff = ((int16_t) ((gyro_data[0] << 8)| gyro_data[1]));
    
    printf("gyro_buff_z: %d\n", gyro_buff);

    return i2c_state;
}

BNO055_STATE_T BNO055_get_calib_status(){

    I2C_STATE_T i2c_state   = I2C_WRITE_ERROR;
    uint8_t calib_data      = 0;
    
    int8_t sys_calib_status = 0;
    int8_t gyr_calib_status = 0;
    int8_t acc_calib_status = 0;
    int8_t mag_calib_status = 0;

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_CALIB_STAT_ADDR, &calib_data, 1);

    // bits 7,6,
    sys_calib_status = (calib_data & 0xC0);
    // bits 5,4
    gyr_calib_status = (calib_data & 0x30);
    // bits 3,2
    acc_calib_status = (calib_data & 0x0C);
    // bits 1,0
    mag_calib_status = (calib_data & 0x03);

    printf("sys_calib_status =  0x%02X\n", sys_calib_status);
    printf("gyr_calib_status =  0x%02X\n", gyr_calib_status);
    printf("acc_calib_status =  0x%02X\n", acc_calib_status);
    printf("mag_calib_status =  0x%02X\n", mag_calib_status);

    return i2c_state;
}

BNO055_STATE_T BNO055_start_selftest(){

    // device supports Built-In Self-Test (BIST)
    // see datasheet 3.9.2 Built-In Self-Test (BIST)
    
    I2C_STATE_T i2c_state   = I2C_WRITE_ERROR;
    uint8_t selftest        = 0x01;
    uint8_t sysError        = 0xFF;


    i2c_state = default_i2c_reg_write(BNO055_ADDR, BNO055_SYS_TRIGGER_ADDR, &selftest, 1);
    printf("Triggered selftest...\n");

    sleep_ms(400);

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_SYS_ERROR_ADDR, &sysError, 1);

    if (sysError == 0)
    {
        printf("Selftest was successfull!\n");
    }else{
        i2c_state = BNO055_selftest_results();
    }

    return i2c_state;
}

BNO055_STATE_T BNO055_selftest_results(){
    
    I2C_STATE_T i2c_state   = I2C_WRITE_ERROR;
    uint8_t st_results      = 0;
    
    uint8_t mcu_st_results = 0;
    uint8_t gyr_st_results = 0;
    uint8_t acc_st_results = 0;
    uint8_t mag_st_results = 0;

    i2c_state = default_i2c_reg_read(BNO055_ADDR, BNO055_CALIB_STAT_ADDR, &st_results, 1);

    // bit 3
    mcu_st_results = (st_results  & 0x07);
    // bit 2
    gyr_st_results = (st_results  & 0x03);
    // bit 1
    acc_st_results = (st_results  & 0x02);
    // bit 0
    mag_st_results = (st_results  & 0x01);

    printf("mcu_st_results =  0x%02X\n", mcu_st_results);
    printf("gyr_st_results =  0x%02X\n", gyr_st_results);
    printf("acc_st_results =  0x%02X\n", acc_st_results);
    printf("mag_st_results =  0x%02X\n", mag_st_results);

    return i2c_state;
}
