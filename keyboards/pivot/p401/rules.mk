MCU = STM32F401
BOARD = GENERIC_STM32_F401XC

KEYBOARD_SHARED_EP       = yes

BOOTLOADER = custom
UF2_FAMILY = 0xabcdf401
FIRMWARE_FORMAT = uf2
MCU_LDSCRIPT=QF_STM32F401

PRODUCE_401_LIB_IND = Y
BOOTMAGIC_ENABLE = no
UARTENABLE = yes
EXTRAKEY_ENABLE = yes

NKRO_ENABLE = no
DEBUG_ENABLE = no

BuildFolder = ../pivot/p401
VPATH += $(TOP_DIR)/keyboards/pivot/stm32
VPATH += $(TOP_DIR)/keyboards/pivot/p401

SRC += ../uart_serial_l.c
SRC += ../pivot/stm32/stm32_qf.c

SRC += ${BuildFolder}/actionuart.c

SRC += ${BuildFolder}/keymapcallback.c
SRC += ${BuildFolder}/process_record_qf.c
SRC += ${BuildFolder}/main_master.c
SRC += ${BuildFolder}/outputselect.c
SRC += ${BuildFolder}/powermstop.c


OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
OPT_DEFS += -DQMK_MCU_STM32F401
OPT_DEFS += -DBOOTLOADER_TINYUF2
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy

OPT = s
