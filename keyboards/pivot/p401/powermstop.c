#include QMK_KEYBOARD_H
#include "hal_pal.h"
#include "powermstop.h"
#include "outputselect.h"
#include "uart.h"
#include "config.h"
#include "actionuart.h"
#include "stm32_qf.h"

void Sys_Stop(void) {
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

    PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_LPDS);
    PWR->CR |= (PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    __DSB();
    __WFI();

    chSysLock();

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    PWR->CR |= PWR_CR_CWUF; // Clear Wakeup Flag
    PWR->CR |= PWR_CR_CSBF; // Clear Wakeup Flag

    stm32_clock_init();
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

     NVIC_SystemReset();
}

#include "usb_util.h"
#include "usb_main.h"
void        pre_process_before_sleep(void) {
    extern void rgb_power_enable(bool enable);

    if (power_pin_enable()) {
        if (rgb_matrix_config.enable) {
            rgb_matrix_disable();
            wait_ms(50);

            xprintf("rgblight_config set to false ...\n");
        }
    }
    // Close power for RGB no matter used or not
    rgb_power_enable(false);
    setWKPin_low();
    wait_ms(50);

    turnOFF_usb_led();
    turnoff_power_led();

    turnoff_caps_led();
    usb_disconnect();
    wait_ms(10);
}

void handle_wk_event(void) {
    const uint32_t *row_pins = get_row_pins();
    const uint32_t *col_pins = get_col_pins();

    uint8_t rows_length   = get_row_length();
    uint8_t cols_length   = get_col_length();
    pin_t   wireDetectPin = get_handwire_detect_pin();

    if (ENCODERS_PAD_A_enable()) {
        // 赋值
        pin_t *encoderA = getEncodersPadA();
        pin_t *encoderB = getEncodersPadB();

        // 解引用
        pin_t xa = *encoderA;
        pin_t xb = *encoderB;

        palSetLineMode(xa, PAL_MODE_INPUT_PULLUP);
        palEnableLineEvent(xa, PAL_EVENT_MODE_FALLING_EDGE);
        palSetLineMode(xb, PAL_MODE_INPUT_PULLUP);
        palEnableLineEvent(xb, PAL_EVENT_MODE_FALLING_EDGE);
    }

    palSetLineMode(wireDetectPin, PAL_MODE_INPUT_PULLDOWN);
    palEnableLineEvent(wireDetectPin, PAL_EVENT_MODE_RISING_EDGE);

    if (getDIODE_DIRECTION() == ROW2COL) {
        for (uint32_t i = 0; i < cols_length; i++) {
            setPinOutput(col_pins[i]);
            writePinLow(col_pins[i]);
        }

        for (uint32_t i = 0; i < rows_length; i++) {
            palSetLineMode(row_pins[i], PAL_MODE_INPUT_PULLUP);
            palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_FALLING_EDGE);
        }

    } else {
        for (uint32_t i = 0; i < cols_length; i++) {
            setPinOutputPushPull(col_pins[i]);
        }

        for (uint32_t i = 0; i < rows_length; i++) {
            palSetLineMode(row_pins[i], PAL_MODE_INPUT_PULLDOWN);
            palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_RISING_EDGE);
        }
    }
}

void WKUP_InitStopModeN(void) {
    pre_process_before_sleep();
    handle_wk_event();
    Sys_Stop();
}

void qf_bootloader_jump(void) {
    uint32_t *p = (uint32_t *)0x2000FC00;
    *p = 0xc220b134;
    NVIC_SystemReset();
}
