#include QMK_KEYBOARD_H

#include "outputselect.h"
#include "usb_util.h"
#include "eeconfig.h"
#include "actionuart.h"

uint8_t desired_output = OUTPUT_DEFAULT;
uint8_t manualMode = 0;
uint8_t rgb_matrix_qf_status = 0;


static uint32_t rgb_wire_status = 0;
static uint32_t kb_lock_status = 0;

void set_kb_lock_status(uint32_t kb_lock_statuss) {
    kb_lock_status =kb_lock_statuss;
}

uint32_t get_kb_lock_status(void) {
    return  kb_lock_status;
}

void set_rgb_wire_status(uint32_t rgb_wire_status) {
    rgb_wire_status =rgb_wire_status;
}

uint32_t get_rgb_wire_status(void) {
    return  rgb_wire_status;
}


void set_rgb_matrix_qf_status(uint8_t status) {

    rgb_matrix_qf_status =status;
}

uint8_t get_rgb_matrix_qf_status(void) {

    return  rgb_matrix_qf_status;
}

void set_output(uint8_t output) {

    set_output_user(output);
    //eeconfig_update_user((uint32_t)output);
}

void set_output_default(uint8_t output) {
    desired_output = output;
}

/** \brief Set Output User
 *
 * FIXME: Needs doc
 */
__attribute__((weak)) void set_output_user(uint8_t output) {
    desired_output = output;
    manualMode = 1;
}

/** \brief Auto Detect Output
 *
 * FIXME: Needs doc
 */
uint8_t auto_detect_output(void) {
   if (usb_connected_state()) {
        return OUTPUT_USB;
    }

    return OUTPUT_BLUETOOTH;  // should check if BT is connected here

}

#include "hal_pal.h"

uint8_t previousMode = OUTPUT_DEFAULT;

uint8_t get_mode_before_sleep(void){
    return previousMode;
}

#include "actionuart.h"
uint8_t where_to_send(void) {

  uint8_t currMode = desired_output;

    extern void restart_usb_driver(USBDriver *usbp);
    extern void platform_setup(void);
    // extern void protocol_init(void);
    extern void protocol_setup(void);
    extern void keyboard_setup(void);
    extern void protocol_post_init(void);
    extern void set_init_raw(void);

    if(previousMode != currMode){

            if(currMode == OUTPUT_BLUETOOTH) {

                setWKPin_high();

                turnOFF_usb_led();
                    xprintf("writeHighPinOut  WK_PIN to high !!!\n");

            }else{
                if(keymap_config.nkro == 0){
                    // keymap_config.nkro = 1;
                    xprintf("open nkro for usb mode !!!\n");
                }
                QF_RESET;

            }
            previousMode = currMode;
            xprintf("currMode sssss is %d!!\n",currMode);
        }


    return currMode;
}
