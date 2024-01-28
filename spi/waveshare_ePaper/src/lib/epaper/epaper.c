#include "../include/epaper.h"

#define EPD_1IN54_V2_WIDTH       200
#define EPD_1IN54_V2_HEIGHT      200

#define PIN_CS   9

static void epaper_reset(epaper_params_t* pt_epaper_params);
static void epaper_send_command(epaper_params_t* pt_epaper_params, uint8_t reg);
static void epaper_send_data(epaper_params_t* pt_epaper_params, uint8_t data);
static void epaper_busy_wait(epaper_params_t* pt_epaper_params);
static void epaper_turn_on_full_display(epaper_params_t* pt_epaper_params);
static void epaper_turn_on_partial_display(epaper_params_t* pt_epaper_params);
static void epaper_set_lut(epaper_params_t* pt_epaper_params, uint8_t* pt_lut);
static void epaper_set_window(epaper_params_t* pt_epaper_params);
static void epaper_set_cursor(epaper_params_t* pt_epaper_params);

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS , 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS , 1);
    asm volatile("nop \n nop \n nop");
}


// for EPD_1in54_V2

// waveform full refresh
uint8_t WF_Full_1IN54[159] = {											
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 1
0x0,	0x0,    0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,  // 2 	
0x0,	0x0,	0x0,	0x0,    0x80,	0x48,	0x40,	0x0,	0x0,	0x0,  // 3
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,    0x40,	0x48,	0x80,	0x0,  // 4	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,    0x0,	0x0,  // 5	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 6
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x8,	0x1,	0x0,  // 7	
0x8,	0x1,	0x0,	0x2,	0xA,	0x0,	0x0,	0x0,	0x0,	0x0,  // 8	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 9	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 10
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 11	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 12	
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 13					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,  // 14	
0x0,	0x0,	0x0,	0x0,	0x22,	0x22,	0x22,	0x22,	0x22,	0x22, // 15	
0x0,	0x0,	0x0,	0x22,	0x17,	0x41,	0x0,	0x32,	0x20};

epaper_status_e epaper_init(epaper_params_t* pt_epaper_params){

    epaper_status_e epaper_status = EPAPER_INIT_ERROR;

    local_spi_init(&pt_epaper_params->spi_params);

    pt_epaper_params->x_start   = 0;
    pt_epaper_params->x_end     = EPD_1IN54_V2_WIDTH-1;

    pt_epaper_params->y_start   = EPD_1IN54_V2_HEIGHT-1;
    pt_epaper_params->x_end     = 0;

    //pt_epaper_params->imagesize = ((EPD_1IN54_V2_WIDTH% 8 == 0)? (EPD_1IN54_V2_WIDTH/ 8 ): (EPD_1IN54_V2_WIDTH/ 8 + 1)) * EPD_1IN54_V2_HEIGHT * 2;
    pt_epaper_params->imagesize = 10000;

    pt_epaper_params->epaper_picture.pic_width  = EPD_1IN54_V2_WIDTH;
    pt_epaper_params->epaper_picture.pic_height = EPD_1IN54_V2_HEIGHT;
    pt_epaper_params->epaper_picture.pic_width_memory  = EPD_1IN54_V2_WIDTH;
    pt_epaper_params->epaper_picture.pic_height_memory = EPD_1IN54_V2_HEIGHT;
    pt_epaper_params->epaper_picture.pic_scale      = 2;
    pt_epaper_params->epaper_picture.pic_rotate = 0;
    pt_epaper_params->epaper_picture.pic_mirror = 0;
    pt_epaper_params->epaper_picture.pic_color  = 0xFF; // WHITE

    pt_epaper_params->epaper_picture.pic_width_byte     = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    pt_epaper_params->epaper_picture.pic_height_byte    = EPD_1IN54_V2_HEIGHT;

    epaper_status = epaper_display_init(pt_epaper_params);
    epaper_status = epaper_clear_display(pt_epaper_params);

    epaper_status = EPAPER_ALL_GOOD;

    printf("epaper init done\n");

    return epaper_status;
}

epaper_status_e epaper_display_init(epaper_params_t* pt_epaper_params){

    epaper_status_e epaper_status = EPAPER_INIT_ERROR;

    epaper_reset(pt_epaper_params);

    // software reset
    epaper_busy_wait(pt_epaper_params);
    epaper_send_command(pt_epaper_params, 0x12);  //SWRESET
    epaper_busy_wait(pt_epaper_params);

    // send init code 
    epaper_send_command(pt_epaper_params, 0x01); //Driver output control
    epaper_send_data(pt_epaper_params, 0xC7);
    epaper_send_data(pt_epaper_params, 0x00);
    epaper_send_data(pt_epaper_params, 0x01);

    epaper_send_command(pt_epaper_params, 0x11); //data entry mode
    epaper_send_data(pt_epaper_params, 0x01);

    epaper_set_window(pt_epaper_params);

    epaper_send_command(pt_epaper_params, 0x3C); //BorderWavefrom
    epaper_send_data(pt_epaper_params, 0x01);

    epaper_send_command(pt_epaper_params, 0x18);
    epaper_send_data(pt_epaper_params, 0x80);

    epaper_send_command(pt_epaper_params, 0x22); // //Load Temperature and waveform setting.
    epaper_send_data(pt_epaper_params, 0XB1);
    epaper_send_command(pt_epaper_params, 0x20);

    epaper_set_cursor(pt_epaper_params);
    epaper_busy_wait(pt_epaper_params);

    epaper_set_lut(pt_epaper_params, WF_Full_1IN54);

    epaper_status = EPAPER_ALL_GOOD;

    printf("epaper_display_init done\n");

    return epaper_status;
}

epaper_status_e epaper_clear_display(epaper_params_t* pt_epaper_params){

    epaper_status_e epaper_status = EPAPER_INIT_ERROR;

    uint8_t width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    uint8_t height = EPD_1IN54_V2_HEIGHT;

    epaper_send_command(pt_epaper_params, 0x24);
    for (uint8_t j = 0; j < height; j++) {
        for (uint8_t i = 0; i < width; i++) {
            epaper_send_data(pt_epaper_params, 0XFF);
            //printf("clear_display send: 0XFF on pos: %d, %d\n", j, i);
        }
    }
    epaper_send_command(pt_epaper_params, 0x26);
    for (uint8_t j = 0; j < height; j++) {
        for (uint8_t i = 0; i < width; i++) {
            epaper_send_data(pt_epaper_params, 0XFF);
            //printf("clear_display send: 0XFF on pos: %d, %d\n", j, i);
        }
    }
    epaper_turn_on_full_display(pt_epaper_params);

    epaper_status = EPAPER_ALL_GOOD;
    printf("epaper_clear_display done\n");

    return epaper_status;
}

epaper_status_e epaper_paint_color(epaper_params_t* pt_epaper_params){

    epaper_status_e epaper_status = EPAPER_INIT_ERROR;

    uint32_t byte_addr = 0;

    for (size_t y = 0; y < pt_epaper_params->epaper_picture.pic_height_byte; y++)
    {
        for (size_t x = 0; x < pt_epaper_params->epaper_picture.pic_width_byte; x++)
        {
            byte_addr = x + y * pt_epaper_params->epaper_picture.pic_width_byte;
            pt_epaper_params->epaper_picture.pt_image[byte_addr] = pt_epaper_params->epaper_picture.pic_color;
        }   
    }

    epaper_status = EPAPER_ALL_GOOD;
    printf("epaper_paint_color done\n");

    return epaper_status;
}

epaper_status_e epaper_draw_bitmap(epaper_params_t* pt_epaper_params, const unsigned char* image_buffer)
{
    epaper_status_e epaper_status = EPAPER_INIT_ERROR;
    uint16_t x, y;
    uint32_t addr = 0;

    for (y = 0; y < pt_epaper_params->epaper_picture.pic_height_byte; y++) {
        for (x = 0; x < pt_epaper_params->epaper_picture.pic_width_byte; x++) {//8 pixel =  1 byte
            addr = x + y * pt_epaper_params->epaper_picture.pic_width_byte;
            pt_epaper_params->epaper_picture.pt_image[addr] = (unsigned char)image_buffer[addr];
        }
    }

    epaper_status = EPAPER_ALL_GOOD;
    printf("epaper_draw_bitmap\n");

    return epaper_status;
}

epaper_status_e epaper_send_to_display(epaper_params_t* pt_epaper_params)
{
    epaper_status_e epaper_status = EPAPER_INIT_ERROR;
    uint16_t width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    uint16_t height = EPD_1IN54_V2_HEIGHT;
    uint32_t addr = 0;

    epaper_send_command(pt_epaper_params, 0x24);
    for (uint16_t j = 0; j < width; j++) {
        for (uint16_t i = 0; i < height; i++) {
            addr = i + j * width;
            epaper_send_data(pt_epaper_params, pt_epaper_params->epaper_picture.pt_image[addr]);
        }
    }
    epaper_turn_on_full_display(pt_epaper_params);

    epaper_status = EPAPER_ALL_GOOD;
    printf("epaper_send_to_display\n");

    return epaper_status;
}

static void epaper_reset(epaper_params_t* pt_epaper_params){

    // pull rs high for 10 ms
    gpio_put(pt_epaper_params->spi_params.spi_rs_pin, 1);
    sleep_ms(200);
    // pull rs low for 2 ms
    gpio_put(pt_epaper_params->spi_params.spi_rs_pin, 0);
    sleep_ms(2);
    // pull rs high for 10 ms
    gpio_put(pt_epaper_params->spi_params.spi_rs_pin, 1);
    sleep_ms(0);
}

static void epaper_send_command(epaper_params_t* pt_epaper_params, uint8_t reg){

    // Data Control (DC) must be low for writing commands
    gpio_put(pt_epaper_params->spi_params.spi_rx_pin, 0);
    cs_select();
    (void) spi_write(&reg, 1);
    cs_deselect();
}

static void epaper_send_data(epaper_params_t* pt_epaper_params, uint8_t  data){

    // Data Control (DC) must be high for writing data
    gpio_put(pt_epaper_params->spi_params.spi_rx_pin, 1);
    cs_select();
    (void) spi_write(&data, 1);
    cs_deselect();
}

static void epaper_busy_wait(epaper_params_t* pt_epaper_params){

    while((gpio_get(pt_epaper_params->spi_params.spi_busy_pin)) == 1) {      //LOW: idle, HIGH: busy
        printf("busy waiting \n");
        sleep_ms(10);
    }
    printf("busy was idle \n");
    
}

static void epaper_turn_on_full_display(epaper_params_t* pt_epaper_params){
    
    epaper_send_command(pt_epaper_params, 0x22);
    epaper_send_data(pt_epaper_params, 0xC7);
    epaper_send_command(pt_epaper_params, 0x20);
    epaper_busy_wait(pt_epaper_params);
}

static void epaper_turn_on_partial_display(epaper_params_t* pt_epaper_params){

    epaper_send_command(pt_epaper_params, 0x22);
    epaper_send_data(pt_epaper_params, 0xCF);
    epaper_send_command(pt_epaper_params, 0x20);
    epaper_busy_wait(pt_epaper_params);
}

static void epaper_lut(epaper_params_t* pt_epaper_params, uint8_t* pt_lut){
    
	epaper_send_command(pt_epaper_params, 0x32);
    for (size_t i = 0; i < 153; i++)
    {
        epaper_send_data(pt_epaper_params, pt_lut[i]);
        printf("lut send: 0x%02X on pos: %d\n", pt_lut[i], i);
    }
    epaper_busy_wait(pt_epaper_params);
}

static void epaper_set_lut(epaper_params_t* pt_epaper_params, uint8_t* pt_lut){
    epaper_lut(pt_epaper_params, pt_lut);
	
    epaper_send_command(pt_epaper_params, 0x3F);
    epaper_send_data(pt_epaper_params, pt_lut[153]);
	
    epaper_send_command(pt_epaper_params,0x03);
    epaper_send_data(pt_epaper_params, pt_lut[154]);
	
    epaper_send_command(pt_epaper_params, 0x04);
    epaper_send_data(pt_epaper_params, pt_lut[155]);
	epaper_send_data(pt_epaper_params, pt_lut[156]);
	epaper_send_data(pt_epaper_params, pt_lut[157]);
	
	epaper_send_command(pt_epaper_params, 0x2C);
    epaper_send_data(pt_epaper_params, pt_lut[158]);
}

static void epaper_set_window(epaper_params_t* pt_epaper_params){

    epaper_send_command(pt_epaper_params, 0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->x_start) >>3) & 0xFF);
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->x_end)>>3) & 0xFF);
	
    epaper_send_command(pt_epaper_params, 0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_start) & 0xFF));
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_start) >> 8) & 0xFF);
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_end) & 0xFF));
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_end) >> 8) & 0xFF);
}

static void epaper_set_cursor(epaper_params_t* pt_epaper_params){

    epaper_send_command(pt_epaper_params, 0x4E); // SET_RAM_X_ADDRESS_COUNTER
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->x_start) & 0xFF));

    epaper_send_command(pt_epaper_params, 0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_start) & 0xFF));
    epaper_send_data(pt_epaper_params, ((pt_epaper_params->y_start) >> 8) & 0xFF);
}
