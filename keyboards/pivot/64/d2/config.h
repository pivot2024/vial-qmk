#pragma once


#define QF_ADC_PIN B0

#define LED_CAPS_LOCK_PIN A8
#define USB_PIN_LED B8
#define WK_PIN C14

#undef HAND_WIRE_DETECT
#define HAND_WIRE_DETECT C5

#define QF_LED_COUNT 64

#undef RGBLED_NUM
#define RGBLED_NUM 64

#define POWER_PIN C7
#define POWER_LED B3

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS     { A0, A1,A2,A3, A4}
#define MATRIX_COL_PINS     { A5, A6, B1 ,B10, B13,   B14,B15,C6,B9,C12,  B4,B5,B6,B7}


#define SLEEP_SEC 800


#define RADIO_LED_INDEX 18
#define BLE1_LED_INDEX 15
#define BLE2_LED_INDEX 16
#define BLE3_LED_INDEX 17

#define CAPS_LED_INDEX 28
#define RGB_BLE_LED
