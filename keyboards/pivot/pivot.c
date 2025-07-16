#include "pivot.h"
#include "bootmagic.h"


void bootmagic_scan(void) {

}
#include "host_driver.h"
#include "report.h"
/* declarations */
uint8_t keyboard_leds(void);
void    send_keyboard(report_keyboard_t *report);
void    send_nkro(report_nkro_t *report);
void    send_mouse(report_mouse_t *report);
void    send_extra(report_extra_t *report);

