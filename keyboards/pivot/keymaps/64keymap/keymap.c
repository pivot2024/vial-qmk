#include QMK_KEYBOARD_H

#include "quantum.h"

#include "dynamic_keymap.h"
#include "uart.h"

#include "hal_pal.h"
#include "main_master.h"



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [0] = { \
    { KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,      KC_5,   KC_6,  KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC}, \
    { KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,      KC_T,  KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS}, \
    { KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,      KC_G,  KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_NO}, \
    { KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,      KC_B,  KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_DEL}, \
    { KC_LCTL ,KC_LGUI,KC_LALT,KC_SPC, KC_NO,     KC_NO, KC_NO, KC_NO,   KC_NO,  MO(2), MO(1),   KC_LEFT, KC_DOWN, KC_RGHT} \
  },
 [1] = { \
   { QK_BOOT,   KC_F1,  KC_F2,  KC_F3,  KC_F4,     KC_F5, KC_F6,  KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC}, \
    { KC_GRV, BL_SW_1,BL_SW_2,BL_SW_3,   RADIO, KC_T,  KC_Y,   KC_U,    KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS}, \
    { KC_CAPS, KC_A,   RGB_MODE_FORWARD,   RGB_TOG,   KC_F,      KC_G,  KC_H,   KC_J,    KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT, KC_NO}, \
    { KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,      KC_NO,  KC_N,   KC_M,    KC_COMM,KC_DOT,  KC_SLSH, KC_RSFT, RGB_VAI,   BLE_DEL}, \
    { KC_LCTL ,KC_LGUI,KC_LALT,KC_SPC, KC_NO,     KC_NO, KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_LEFT,   RGB_VAD,   KC_RGHT} \
  },
 [2] = { \
   { QK_BOOT,   KC_F1,  KC_F2, KC_F3,  KC_F4,     KC_F5, KC_F6,  KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC}, \
    { KC_GRV,  KC_Q,   KC_W,   KC_E,   KC_R, KC_T,  KC_Y,   KC_U,    KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS}, \
    { KC_CAPS, KC_A,   KC_S,   RGB_TOG,   KC_F,      KC_G,  KC_H,   KC_J,    KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT, KC_NO}, \
    { KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,      KC_NO,  KC_NO,   KC_M,    KC_COMM,KC_DOT,  KC_SLSH, KC_RSFT, RGB_VAI,   BLE_DEL}, \
    { KC_LCTL ,KC_LGUI,KC_LALT,KC_SPC, KC_NO,     KC_NO, KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_LEFT,   RGB_VAD,   KC_RGHT} \
  }
};


#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        { 0,  1,     2,  3,      4,  5,      6,      7,      8,      9,  10,  11,   12,      13 },
        { 14, 15,    16, 17,     18, 19,     20,     21,     22,     23, 24,  25,   26,      27 },
        { 28 ,29,    30, 31,     32, 33,     34,     35,     36,     37, 38,  39,   40,  NO_LED },
        { 41, 42,    43, 44,     45, 46,     47,     48,     49,     50, 51,  52,   53,      54 },
        { 55, 56,    57, 58,  NO_LED,NO_LED, NO_LED, NO_LED, NO_LED, 59, 60,  61,   62,      63 }
    }, {
        // Key matrix (0 -> 63)
    {0  ,  0}, {16 ,  0}, {32 ,  0}, {48 ,  0}, {64 ,  0}, {80 ,  0}, {96 ,  0}, {112,  0}, {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {216,  0},
    {4  , 16}, {24 , 16}, {40 , 16}, {56 , 16}, {72 , 16}, {88 , 16}, {104, 16}, {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16},
    {6  , 32}, {28 , 32}, {44 , 32}, {60 , 32}, {76 , 32}, {92 , 32}, {108, 32}, {124, 32}, {140, 32}, {156, 32}, {172, 32}, {188, 32}, {194, 32} ,
    {8  , 48}, {32 , 48}, {48 , 48}, {64 , 48}, {80 , 48}, {96 , 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48}, {224, 48},
    {2  , 64}, {22 , 64}, {42 , 64},                       {102, 64},                                  {160, 64}, {176, 64}, {192, 64}, {208, 64}, {224, 64},

}, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1,          1,       1, 1, 1, 1, 1
    }
};

 bool rgb_matrix_indicators_kb(void) {
     if (host_keyboard_led_state().caps_lock) {  // Capslock = RED
         rgb_matrix_set_color(CAPS_LED_INDEX, 0, 200, 0);
     }
     return true;
 }
#endif


bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
    }
    return res;
}
