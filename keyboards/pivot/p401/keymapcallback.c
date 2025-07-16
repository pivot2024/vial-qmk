#include <stdint.h>
#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>
#include "dynamic_keymap.h"
#include "uart.h"
#include "outputselect.h"

#include "hal_pal.h"
#include "powermstop.h"
#include "actionuart.h"
#include "main_master.h"
#include "usb_util.h"
#include "usb_main.h"
#include "actionuart.h"
#include "matrix.h"


uint32_t previousTimeslot = 0;

uint32_t initModeChannel = 0;
static uint32_t sleep_timer = 0;
 uint32_t counterD = 1;
uint8_t enable_auto_switch = 1; // 1 means auto switch, 0 means hand switch

void handle_first_second_work(uint32_t elapT){
    if (initModeChannel == 0 && elapT > 1) {
        // Initialize UART with baud rate of 115200
        uart_init(115200);

        // Call flyInit function
        flyInit();

        // Set initModeChannel to 1
        initModeChannel = 1;

        if(power_pin_enable() ){
             // Enable RGB power if configured
            if (rgb_matrix_config.enable) {
                rgb_power_enable(true);
            }
        }

    }
}
extern  void send_hid_key_release(void);
void auto_switch_mode(uint8_t usb_detect1){
    if(enable_auto_switch == 1){

        if(usb_detect1 == 1){
            if (where_to_send() != OUTPUT_USB) {
                send_hid_key_release();

                set_output(OUTPUT_USB);
                xprintf("Mode to USB!!!\n");
                showPerChannel2();

            }

            setWKPin_low();
        }


        if(usb_detect1 == 0){
            if (where_to_send() == OUTPUT_USB) {
                send_hid_key_release();
                set_output(OUTPUT_BLUETOOTH);
                xprintf("Mode to BLE!!!\n");
            }
            setWKPin_high();
        }

    }

}

void prepare_and_go_sleep(void){
        if (where_to_send() == OUTPUT_USB) {
            counterD=0;
            return;
        }

        counterD=0;
        WKUP_InitStopModeN();
        initModeChannel=0;
}

uint8_t has_key_press(void) {
    uint8_t rows_length = get_row_length();

    bool matrix_has_keys = false;
    for (uint8_t row = 0; row < rows_length; row++) {
        const matrix_row_t current_row = matrix_get_row(row);
        if (current_row != 0) {
            matrix_has_keys = true;
        }
    }

    /**
     * Matrix changes or there are keys inside the matrix
     */
    if (matrix_has_keys == true) {
        return 1;
    }

    return 0;
}

uint32_t count_fre = 0;
uint32_t pre_count_fre = 0;
void matrix_scan_user_qf(void) {


    count_fre++;

    uint32_t elapT= timer_elapsed32(sleep_timer)/1000;
    handle_first_second_work(elapT);
    if(elapT != previousTimeslot){
        counterD++;

        pre_count_fre = count_fre;
        if(elapT % 2 == 0){

            //  uint8_t usb_detect1 = read_handwire_detect();
             xprintf("Sec %ld, wire - %d, rgb_matrix_config - %d mode is %d\n", counterD, usb_detect1, rgb_matrix_config.enable,where_to_send());

        }

        uint8_t usb_detect1 = read_handwire_detect();

        auto_switch_mode(usb_detect1);

        previousTimeslot = elapT;

        uint32_t sleepSec = SLEEP_SEC;

        if(power_pin_enable()){

            if(rgb_matrix_is_enabled()) {
                sleepSec = getSLEEP_SEC_RGB();
            }
        }


        if(counterD > sleepSec ) {
            prepare_and_go_sleep();
        }

     }
}

void process_rgb_tog(void){

    if(power_pin_enable() == false){
        return;
    }
    extern rgb_config_t rgb_matrix_config;
    if(rgb_matrix_config.enable) {
        set_rgb_matrix_qf_status(0);
        rgb_matrix_disable();
        wait_ms(50);
        rgb_power_enable(false);

        xprintf("rgblight_config set to false ...\n");
    } else {
        set_rgb_matrix_qf_status(1);
        rgb_power_enable(true);

        xprintf("rgblight_config set to true ...\n");
        rgb_matrix_enable();
        wait_ms(50);
    }
}


extern void set_init_raw(void);
void board_init_qf(void) {

    setHandWireLow();
    set_init_raw();

    uart_init(115200);
}
