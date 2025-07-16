
#pragma once

#include <stdint.h>
#include "pivot.h"

#define QF_LED_EMPTY -1

#define GPIO_PIN_INVALID -1 // 自定义无效引脚常量
#define SLEEPCODE 0x02
#define PAIRCODE 0x03

#define UNPAIRCODE 0x04
#define RESET_CODE 0x05


#define CHANNAL_001 0x07
#define CHANNAL_002 0x08
#define CHANNAL_003 0x09
#define CHANNAL_RADIO 0x0A
#define MUL_MEDIA 0x0B
#define KB_SYSTEM 0x0C


pin_t get_CHANNEL0_LED_PIN_pin(void);
pin_t get_CHANNEL1_LED_PIN_pin(void);
pin_t get_CHANNEL2_LED_PIN_pin(void);
pin_t get_CHANNEL4_LED_PIN_pin(void);
bool ENCODERS_PAD_A_enable(void);
pin_t* getEncodersPadA(void);
pin_t* getEncodersPadB(void);
uint8_t getDIODE_DIRECTION(void);

bool power_pin_enable(void);
bool readRGBPowerPin(void) ;
bool BLINK_BLE_LED_enable(void);
bool RGB_BLE_LED_enable(void);
bool FN_BLE__RGB_LED_enable(void);


void turnON_usb_led(void);
void turnOFF_usb_led(void);

void turnoff_power_led(void);
void turnon_power_led(void);

void turnon_caps_led(void);
void turnoff_caps_led(void);
bool caps_pin_enable(void);

void setWKPin_high(void);
void setWKPin_low(void);
uint8_t readWKPin(void);
uint8_t read_POWER_LED(void);

uint8_t getCAPS_LED_INDEX(void);
uint8_t getBLE1_LED_INDEX(void);
uint8_t getBLE2_LED_INDEX(void);
uint8_t getBLE3_LED_INDEX(void);
uint8_t getRADIO_LED_INDEX(void);
uint16_t get_RGBLED_NUM(void);
uint16_t getSLEEP_SEC_RGB(void);

void process_LED_status(void);
void rgb_power_enable(bool enable);

uint8_t read_handwire_detect(void);
pin_t get_handwire_detect_pin(void);
void setHandWireLow(void);
void process_handle_wk_event(void);

uint32_t* get_row_pins(void);
uint32_t* get_col_pins(void);

uint8_t get_row_length(void);
uint8_t get_col_length(void);

