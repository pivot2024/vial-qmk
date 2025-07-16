#include <ch.h>
#include <hal.h>
#include <string.h>
#include "report.h"
#include "quantum_keycodes.h"


typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


enum custom_keycodes {
    KC_BLE_1= QK_KB_0,
    KC_BLE_2,
    KC_BLE_3,
    KC_24_G,
    KC_BLE_DEL
};

enum my_keycodes {
  NKRO_GO = SAFE_RANGE,
  SIX_KEY_GO,
  MANU_MODE,
  DFU_QF
};


typedef enum {
  SEND_MODE_USB = 0,
  SEND_MODE_UART = 1
} SEND_MODE;

typedef enum  {
  CONNECTION_TYPE_USB = SEND_MODE_USB,
  CONNECTION_TYPE_UART = SEND_MODE_UART,
} CONNECTION_TYPE;


#define BL_SW_1     KC_BLE_1
#define BL_SW_2     KC_BLE_2
#define BL_SW_3     KC_BLE_3  // RADIO
#define RADIO     KC_24_G  // RADIO
#define USB_QF     KC_USB_CHANNEL  // USB Channel

#define BAU_TOG USB_QF

#define BLE_DEL     KC_BLE_DEL
#define NKRO_GO     KC_F14  // GO NKRO
#define SIX_KEY_GO     KC_F15  // GO 6KEY


void send_keyboard_qf(report_keyboard_t *report);
void send_keyboard(report_keyboard_t *report);
void send_extra_qf(report_extra_t *report) ;
void send_extra(report_extra_t *report) ;

void send_mouse_qf(report_mouse_t *report);
void send_mouse(report_mouse_t *report);
void send_consumer_qf(uint16_t report);
void send_consumer(uint16_t report);
void send_system_qf(uint16_t report) ;
void send_system(uint16_t report) ;


