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

#include "usb_util.h"
#include "usb_main.h"

#include "main_master.h"

extern uint32_t counterD;
extern uint8_t  enable_auto_switch;

extern rgb_config_t rgb_matrix_config;


bool process_record_user_qf(uint16_t keycode, keyrecord_t *record) {
     if (record->event.pressed) {
        counterD = 1;
    }
    switch(keycode) {
        case BL_SW_1:
                if (record->event.pressed) {
                    channel_common(CHANNAL_001);
                     xprintf("0001\n");
                      set_output(OUTPUT_BLUETOOTH);
                }
            return false;
        case BL_SW_2:
                if (record->event.pressed) {
                    channel_common(CHANNAL_002);
                     set_output(OUTPUT_BLUETOOTH);
                }
            return false;
        case BL_SW_3:
                if (record->event.pressed) {
                    channel_common(CHANNAL_003);
                     set_output(OUTPUT_BLUETOOTH);
                }
            return false;
          case RADIO:
                if (record->event.pressed) {
                     xprintf("radio switched \n");
                    channel_common(CHANNAL_RADIO);
                     set_output(OUTPUT_BLUETOOTH);
                }
            return false;
        case BLE_DEL:
            if (where_to_send() != OUTPUT_USB) {
                if (record->event.pressed) {
                    unpair_current_BLE();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
               extern void process_rgb_tog(void);
               process_rgb_tog();
            }
            return false;
      break;
        default:
            return true;
    }
    return true;
}
