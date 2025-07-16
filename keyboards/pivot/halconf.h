

#pragma once

#define HAL_USE_PWM TRUE
#define HAL_USE_SERIAL TRUE

#define SERIAL_USB_BUFFERS_SIZE 256

#define PAL_USE_WAIT                        TRUE
#define PAL_USE_CALLBACKS                   TRUE

#undef HAL_USE_I2C
#define HAL_USE_I2C FALSE
#undef STM32_SERIAL_USE_USART2
#define STM32_SERIAL_USE_USART2             FALSE
#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3             FALSE


#include_next <halconf.h>
