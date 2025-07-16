
#pragma once
#include QMK_KEYBOARD_H
#include "hal_pal.h"
#include "powermstop.h"
#include "outputselect.h"
#include "uart.h"
#include "pivot.h"
#include "stm32_qf.h"

#define SLEEPCODE 0x02
#define PAIRCODE 0x03

#define UNPAIRCODE 0x04
#define RESET_CODE 0x05
#define ADC_DISPALY_CODE 0x06


#define CHANNAL_001 0x07
#define CHANNAL_002 0x08
#define CHANNAL_003 0x09
#define CHANNAL_RADIO 0x0A
#define MUL_MEDIA 0x0B
#define KB_SYSTEM 0x0C

#define KB_BATTERY 0x0D
#define KB_RADIO_DFU 0x0E


#define SHOWUP_CHANNEL_LED 0x10

void uartSendByAction(uint8_t actionCode);

void pair_blueMode(void);
void unpair_current_BLE(void);
void reset_current_BLE(void);
void flyInit(void);
void writeHighPinOut(pin_t pin);
void switch_cols_gpio_from_3V(pin_t pin);

void writeLowPinOut(pin_t pin);
void showPerChannel2(void);
void bluetooth_switch_one(int swc);

void channel_common(uint8_t ee);

void turn_on_led(pin_t pin);
void turn_off_led(pin_t pin);
void flyInit(void);

void turn_on_led_OD(pin_t pin);
void writeHighPinOutOD(pin_t pin);

void writeLowPinOutOD(pin_t pin);




