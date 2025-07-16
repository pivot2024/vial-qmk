#pragma once

#include <stdbool.h>
#include <stdint.h>
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define QF_RESET do { __set_FAULTMASK(1); NVIC_SystemReset(); } while (0)


#define LAYOUT_ortho_5x14( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,  \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,  \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,  \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D }  \
}

typedef void (*TypeCallbackshort)(void);
typedef void (*TypeCallbacklong)(void);

uint8_t eeconfig_read_MANUAL_MODE_QF(void) ;
void eeconfig_write_MANUAL_MODE_QF(uint8_t from_mode);

uint8_t eeconfig_read_CURRENT_MODE(void) ;

void eeconfig_write_CURRENT_MODE(uint8_t from_mode);
void process_hold_keys_cb(bool hold_pressed,TypeCallbackshort short_cb,TypeCallbacklong long_cb);

void poll_hold_keys_scan(void);
void qf_bootloader_jump(void) ;


