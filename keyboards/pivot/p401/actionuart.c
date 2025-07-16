#include QMK_KEYBOARD_H
#include "hal_pal.h"
#include "actionuart.h"
#include "outputselect.h"
#include "uart.h"
#include "eeconfig.h"
#include "eeprom.h"


void uartSendByAction(uint8_t actionCode){

    xprintf("action code is %x...."+actionCode);

    uart_write(0xFD);

    uart_write(actionCode); //0x02 is to wakeup

    for(int i=0;i<8;i++){
          uart_write(0x01);
    }

    uart_write(0xFF);
}

void writeHighPinOut(pin_t pin){
    setPinOutput(pin);
    writePinHigh(pin);
}


void switch_cols_gpio_from_3V(pin_t pin){
    writeHighPinOut(pin);
}

void writeLowPinOut(pin_t pin){
    setPinOutput(pin);
    writePinLow(pin);
}

void writeHighPinOutOD(pin_t pin){
    setPinOutputOpenDrain(pin);
    writePinHigh(pin);
}

void writeLowPinOutOD(pin_t pin){
    setPinOutputOpenDrain(pin);
    writePinLow(pin);
}

void pair_blueMode(void){
    xprintf("pair_blueMode  ....");
    uartSendByAction(PAIRCODE);
}

void go_bl_dfu(void){
    xprintf("go_bl_dfu ....");
    uartSendByAction(KB_RADIO_DFU);
}

void channel_common(uint8_t channel_v){
    xprintf("channel1 ....");
    uartSendByAction(channel_v);
    showPerChannel2();
}

void unpair_current_BLE(void){
    xprintf("unpair_blueMode to do ....");
    uartSendByAction(UNPAIRCODE);
}

void reset_current_BLE(void){
    xprintf("reset_current_BLE to do ....");
    uartSendByAction(RESET_CODE);
}

void show_adc_power(uint8_t f[]){
    xprintf("show_adc_power.");


    uart_write(0xFD);

    uart_write(ADC_DISPALY_CODE); //0x06 is to adc pass in

    for(int i=0;i<8;i++){
          uart_write(0x01);
    }

    uart_write(0xFF);
}

void bluetooth_switch_one(int swc){
    xprintf("bluetooth_switch_one to do %d....",swc);
    if(swc == 0){
        uartSendByAction(0x05);
         xprintf("Channel 1 %d....",swc);
    }
    if(swc == 1){
        uartSendByAction(0x06);
         xprintf("Channel 2 %d....",swc);
    } if(swc == 2){
        uartSendByAction(0x07);
         xprintf("Channel 3 %d....",swc);
    }

}

// void turn_on_led(pin_t pin){
//     if(pin == QF_LED_EMPTY){
//         return ;
//     }

//     if(LED_ON_HIGH==1){
//         writePinHigh(pin);
//     }else{
//         writePinLow(pin);
//     }
// }

void turn_on_led_OD(pin_t pin){
    if(pin == QF_LED_EMPTY){
        return ;
    }

    if(LED_ON_HIGH==1){
        writeHighPinOutOD(pin);
    }else{
        writePinLow(pin);
    }
}

// void turn_off_led(pin_t pin){

//     //inogre behavior if pin is -1
//     if(pin == QF_LED_EMPTY){
//         return ;
//     }
//     if(LED_ON_HIGH==1){
//         writeLowPinOut(pin);
//     }else{
//         writePinHigh(pin);
//     }
// }


uint8_t showled=0;


void showPerChannel2(void) {
     xprintf("where_to_send is ......%d....", where_to_send());
    if (where_to_send() == OUTPUT_USB) {
         #ifdef DISABLE_USB_LED
           turn_off_led(USB_PIN_LED);
         #else
              turn_on_led(USB_PIN_LED);
        #endif
    } else {
           turn_off_led(USB_PIN_LED);
    }

}

void showLEDInit(void) {
     xprintf("where_to_send is ......%d....", auto_detect_output());

    if (where_to_send() == OUTPUT_USB) {
         #ifdef DISABLE_USB_LED
           turn_off_led(USB_PIN_LED);
         #else
              turn_on_led(USB_PIN_LED);
        #endif
    } else {
         #if defined (USB_PIN_LED)
           turn_off_led(USB_PIN_LED);
         #endif
    }

}


void flyInit(void){

    #if defined(CHANNEL0_LED_PIN)
        turn_off_led(CHANNEL0_LED_PIN);
    #endif

    #if defined(CHANNEL1_LED_PIN)
        turn_off_led(CHANNEL1_LED_PIN);
    //    turn_off_led(CHANNEL1_LED_PIN);
    #endif

    #if defined(CHANNEL2_LED_PIN)
            turn_off_led(CHANNEL2_LED_PIN);
    #endif

    #if defined(CHANNEL4_LED_PIN)
            turn_off_led(CHANNEL4_LED_PIN);
    #endif

    #if defined (CHARGE_DETECT_PIN)
        writeHighPinOutOD(CHARGE_DETECT_PIN);
    #endif

    #if defined (LED_CAPS_LOCK_PIN)
        turn_off_led(LED_CAPS_LOCK_PIN);
    #endif

    #if defined (POWER_LED)
     if(POWER_LED != -1){
        setPinOutput(POWER_LED);
        turn_on_led(POWER_LED);
     }
    #endif

    #if defined (USB_PIN_LED)
        setPinOutput(USB_PIN_LED);
        showLEDInit();
    #endif
    writeHighPinOut(WK_PIN);
    xprintf("This will only init once ....");

}

