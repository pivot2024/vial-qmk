
#pragma once

#include <stdint.h>

enum outputs {
    OUTPUT_AUTO=0,
    OUTPUT_NONE=1,
    OUTPUT_USB=2,
    OUTPUT_BLUETOOTH=3
};
#ifndef OUTPUT_DEFAULT
#    define OUTPUT_DEFAULT OUTPUT_USB
#endif
uint8_t get_mode_before_sleep(void);
void    set_output(uint8_t output);
void    set_output_user(uint8_t output);
void    set_output_default(uint8_t output);
uint8_t auto_detect_output(void);
uint8_t where_to_send(void);
uint8_t get_curr_mode(void);
void set_rgb_matrix_qf_status(uint8_t status);
uint8_t get_rgb_matrix_qf_status(void);

void set_rgb_wire_status(uint32_t rgb_wire_status);

uint32_t get_rgb_wire_status(void);
