#include QMK_KEYBOARD_H
#include "hal_pal.h"
#include "stm32_qf.h"
#include "actionuart.h"
#include "main_master.h"
#define GPIO_PIN_INVALID -1 // 自定义无效引脚常量

u16 RADIO_LED_INDEX_API = RADIO_LED_INDEX;


bool power_pin_inited = false;
void power_pin_init(void) {
  if (power_pin_inited) return;
  power_pin_inited = true;
  #if defined POWER_PIN
  writeLowPinOutOD(POWER_PIN);
  #endif
}
void rgb_power_enable(bool enable) {
  power_pin_init();
  #if defined POWER_PIN
	if (enable) {
         writeHighPinOut(POWER_PIN);
	} else {
		writeLowPinOutOD(POWER_PIN);
    }

  #endif
}


pin_t get_CHANNEL0_LED_PIN_pin(void){
    #ifdef CHANNEL0_LED_PIN
        return CHANNEL0_LED_PIN;
    #else
        return GPIO_PIN_INVALID;
    #endif
}

pin_t get_CHANNEL1_LED_PIN_pin(void){
    #ifdef CHANNEL1_LED_PIN
        return CHANNEL1_LED_PIN;
    #else
        return GPIO_PIN_INVALID;
    #endif
}

pin_t get_CHANNEL2_LED_PIN_pin(void){
    #ifdef CHANNEL2_LED_PIN
        return CHANNEL2_LED_PIN;
    #else
        return GPIO_PIN_INVALID;
    #endif
}

pin_t get_CHANNEL4_LED_PIN_pin(void){
    #ifdef CHANNEL4_LED_PIN
        return CHANNEL4_LED_PIN;
    #else
        return GPIO_PIN_INVALID;
    #endif
}

bool ENCODERS_PAD_A_enable(void){
    #if defined(ENCODERS_PAD_A)
        return true;
    #else
        return false;
    #endif
}

pin_t* getEncodersPadA() {
   #if defined(ENCODERS_PAD_A)
    // Code that uses ENCODERS_PAD_A

        static pin_t encoders_pad_a[] = ENCODERS_PAD_A; // Declare static array to return
        return encoders_pad_a;
    #else
         // Return an empty array
         static pin_t qf_mock[] = {-1};
        return qf_mock; // Return the empty array
    #endif
}

pin_t* getEncodersPadB() {
   #if defined(ENCODERS_PAD_B)
    // Code that uses ENCODERS_PAD_A
        static pin_t encoders_pad_b[] = ENCODERS_PAD_B; // Declare static array to return
        return encoders_pad_b;
    #else
      static  pin_t qf_mock[] = {GPIO_PIN_INVALID};
       return qf_mock;
    #endif
}

uint8_t getDIODE_DIRECTION(void){
    return DIODE_DIRECTION;
}

uint16_t getSLEEP_SEC_RGB(void){
    #ifdef  SLEEP_SEC_RGB
        return SLEEP_SEC_RGB;
    #else
        return 1800;
    #endif
}


bool power_pin_enable(void){
    #if defined(POWER_PIN)
        return true;
    #else
        return false;
    #endif
}
bool caps_pin_enable(void){
    #if defined(LED_CAPS_LOCK_PIN)
        return true;
    #else
        return false;
    #endif
}
bool BLINK_BLE_LED_enable(void){
    #if defined(BLINK_BLE_LED)
        return true;
    #else
        return false;
    #endif
}

bool RGB_BLE_LED_enable(void){
    #if defined(RGB_BLE_LED)
        return true;
    #else
        return false;
    #endif
}


bool FN_BLE__RGB_LED_enable(void){
    #if defined(FN_BLE__RGB_LED)
        return true;
    #else
        return false;
    #endif
}

void turnON_usb_led(void) {
    #if defined (USB_PIN_LED)
    if(USB_PIN_LED != GPIO_PIN_INVALID){
        turn_on_led(USB_PIN_LED);
    }
    #endif
}


void turnOFF_usb_led(void) {
    #if defined (USB_PIN_LED)
    if(USB_PIN_LED != GPIO_PIN_INVALID){
        turn_off_led(USB_PIN_LED);
    }
    #endif
}

void turnoff_power_led(void) {
   #if defined (POWER_LED)
    if(POWER_LED != GPIO_PIN_INVALID){
        turn_off_led(POWER_LED);
    }
   #endif
}

void turnon_power_led(void) {
   #if defined (POWER_LED)
    if(POWER_LED != GPIO_PIN_INVALID){
            turn_on_led(POWER_LED);
    }
   #endif
}


void turnon_caps_led(void){
    #if defined(LED_CAPS_LOCK_PIN)
        turn_on_led(LED_CAPS_LOCK_PIN);
    #endif
}


void turnoff_caps_led(void){
    #if defined(LED_CAPS_LOCK_PIN)
        turn_off_led(LED_CAPS_LOCK_PIN);
    #endif
}

void setWKPin_low(void) {
    writePinLow(WK_PIN);
}


void setWKPin_high(void) {
      writeHighPinOut(WK_PIN);
}

uint8_t readWKPin(void) {
   return readPin(WK_PIN);
}

bool readRGBPowerPin(void) {
   #ifdef POWER_PIN
   return readPin(POWER_PIN);
   #else
   return 0;
   #endif
}


uint8_t getCAPS_LED_INDEX(void) {
   return CAPS_LED_INDEX;
}

uint8_t getBLE1_LED_INDEX(void) {
   return BLE1_LED_INDEX;
}
uint8_t getBLE2_LED_INDEX(void) {
   return BLE2_LED_INDEX;
}
uint8_t getBLE3_LED_INDEX(void) {
   return BLE3_LED_INDEX;
}
uint8_t getRADIO_LED_INDEX(void) {
   return RADIO_LED_INDEX;
}

pin_t get_handwire_detect_pin(void){
    return HAND_WIRE_DETECT;
}

uint8_t read_handwire_detect(void) {
     return readPin(HAND_WIRE_DETECT);
}
uint8_t read_POWER_LED(void) {
    if(POWER_LED == -1){
        return 0;
    }
     return readPin(POWER_LED);
}


void setHandWireLow(void) {
     #if defined (HAND_WIRE_DETECT)
     setPinInputLow(HAND_WIRE_DETECT);
        #endif
}


uint32_t* get_row_pins(void) {
    static uint32_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
    return row_pins;
}

uint32_t* get_col_pins(void) {
    static  uint32_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
    return col_pins;
}

uint8_t get_row_length(void) {
   return MATRIX_ROWS;
}

uint8_t get_col_length(void) {
   return MATRIX_COLS;
}

uint16_t get_RGBLED_NUM(void) {
   return RGBLED_NUM;
}


extern void board_init_qf(void);
void board_init(void) {
    board_init_qf();
}

extern bool process_record_user_qf(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record){
    return process_record_user_qf(keycode, record);
}

extern void qf_bootloader_jump(void);
void bootloader_jump(void){
    qf_bootloader_jump();
}

#define GPIO_PIN_INVALID -1 // 自定义无效引脚常量

extern void matrix_scan_user_qf(void);


void matrix_scan_user(void) {
    matrix_scan_user_qf();
}
