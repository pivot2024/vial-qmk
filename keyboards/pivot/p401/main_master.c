#include <ch.h>
#include <hal.h>
#include <string.h>

#include "usb_main.h"

#include "uart.h"
#include "report.h"
#include "main_master.h"
#include "outputselect.h"
#include "actionuart.h"

void send_extra_qf(report_extra_t *report) {
    uint8_t doutput = where_to_send();

    if (doutput == OUTPUT_BLUETOOTH) {

        uint8_t wk_pin_status = readWKPin();
        if (wk_pin_status == 0) {
            setWKPin_high();
        }

        uint8_t data[2];
        data[0] = (uint8_t)(report->usage >> 8 & 0xFF);
        data[1] = (uint8_t)(report->usage & 0xFF);
        xprintf(" data[0] is %x \n", data[0]); // FD 0b e9 00 ff
        xprintf(" data[1] is %x \n", data[1]); // 00 00 00 00 00

        uart_write(0xFD);

        xprintf(" report_id is %x \n", report->report_id);
        if (report->report_id == REPORT_ID_CONSUMER) {
            //  xprintf(" 22222 ");
            uart_write(MUL_MEDIA);
        }

        if (report->report_id == REPORT_ID_SYSTEM) {
            uart_write(KB_SYSTEM);
        }

        uart_write(data[1]);
        uart_write(data[0]);
        uart_write(0xFF);
    } else {
        if (USB_DRIVER.state != USB_ACTIVE) {
            usbWakeupHost(&USB_DRIVER);
            restart_usb_driver(&USB_DRIVER);
            return;
        }

        send_extra(report);
    }
}

extern uint32_t get_kb_lock_status(void);


void send_hid_key_release(void) {
    report_keyboard_t report = {0};
    send_keyboard_qf(&report);
}
volatile uint32_t modifier_timer_ctl = 0;
void send_keyboard_qf(report_keyboard_t *report) {
    if (get_kb_lock_status() == 1) {
        xprintf("lock status is 1, return \n");
        return;
    }

    uint8_t doutput = where_to_send();

    if (doutput == OUTPUT_BLUETOOTH) {
        uint8_t wk_pin_status = readWKPin();
        if (wk_pin_status == 0) {
            setWKPin_high();
        }

        xprintf("ble mode ...e !!!\n");
        uart_write(0xFD);
        uart_write(0x00);
        uart_write(report->mods);
        uart_write(report->reserved);
        uart_transmit(report->keys, 6);
        uart_write(0xFF);


    } else {

        if (USB_DRIVER.state != USB_ACTIVE) {
            usbWakeupHost(&USB_DRIVER);
            restart_usb_driver(&USB_DRIVER);
            wait_ms(200);
        }

        send_keyboard(report);
    }

    xprintf(" %x ", report->mods);     // FD 0b e9 00 ff
    xprintf(" %x ", report->reserved); // FD 0b e9 00 ff

    xprintf(" %x ", report->keys[0]);   // FD 0b e9 00 ff
    xprintf(" %x ", report->keys[1]);   // FD 0b e9 00 ff
    xprintf(" %x ", report->keys[2]);   // FD 0b e9 00 ff
    xprintf(" %x ", report->keys[3]);   // FD 0b e9 00 ff
    xprintf(" %x ", report->keys[4]);   // FD 0b e9 00 ff
    xprintf(" %x \n", report->keys[5]); // FD 0b e9 00 ff
}

void send_consumer_qf(uint16_t report) {
    uint8_t doutput = where_to_send();

    if (doutput == OUTPUT_BLUETOOTH) {

        uint8_t wk_pin_status = readWKPin();
        if (wk_pin_status == 0) {
            setWKPin_high();
        }

        uint8_t data[2];
        data[0] = (uint8_t)(report >> 8 & 0xFF);
        data[1] = (uint8_t)(report & 0xFF);
        xprintf(" data[0] is %x \n", data[0]); // FD 0b e9 00 ff
        xprintf(" data[1] is %x \n", data[1]); // 00 00 00 00 00

        uart_write(0xFD);
        uart_write(MUL_MEDIA);

        uart_write(data[1]);
        uart_write(data[0]);
        uart_write(0xFF);
    } else {
        if (USB_DRIVER.state != USB_ACTIVE) {
            usbWakeupHost(&USB_DRIVER);
            restart_usb_driver(&USB_DRIVER);
            return;
        }

        send_consumer(report);
    }
}

void send_system_qf(uint16_t report) {
    uint8_t doutput = where_to_send();

    if (doutput == OUTPUT_BLUETOOTH) {
        xprintf(" report is %x \n", report);
        uint8_t data[2];
        data[0] = (uint8_t)(report >> 8 & 0xFF);
        data[1] = (uint8_t)(report & 0xFF);
        xprintf(" data[0] is %x \n", data[0]); // FD 0b e9 00 ff
        xprintf(" data[1] is %x \n", data[1]); // 00 00 00 00 00

        uart_write(0xFD);
        uart_write(KB_SYSTEM);

        uart_write(data[1]);
        uart_write(data[0]);
        uart_write(0xFF);
    } else {
        send_system(report);
    }
}
