#include QMK_KEYBOARD_H
#include "hal_pal.h"
#include "actionuart.h"
#include "outputselect.h"
#include "uart.h"
#include "eeconfig.h"
#include "eeprom.h"

void turn_off_led(pin_t pin){
    if(LED_ON_HIGH==1){
        writePinLow(pin);
    }else{
        writePinHigh(pin);
    }
}

void turn_on_led(pin_t pin){
    if(LED_ON_HIGH==1){
        writePinHigh(pin);
    }else{
        writePinLow(pin);
    }
}
