#ifndef HW_DEF_H_
#define HW_DEF_H_



#include "bsp.h"

#define _DEF_FIRMWATRE_VERSION    "V250529-R1"
#define _DEF_BOARD_NAME           "STM32L4R5Z_Nucleo"

#define _USE_HW_FAULT
#define _USE_HW_RTOS
#define _USE_HW_THREAD

#define _USE_HW_RESET
#define      HW_RESET_BOOT          1

#define _USE_HW_LED
#define      HW_LED_MAX_CH          1
#define      HW_LED_CH_STATUS       _DEF_LED1

#define _USE_HW_UART
#define      HW_UART_MAX_CH         4
#define      HW_UART_CH_SWD         _DEF_UART1
#define      HW_UART_CH_2           _DEF_UART2
#define      HW_UART_CH_3           _DEF_UART3
#define      HW_UART_CH_USB         _DEF_UART4

#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    64
#define      HW_CLI_CMD_NAME_MAX    32
#define      HW_CLI_LINE_HIS_MAX    16
#define      HW_CLI_LINE_BUF_MAX    128

#define _USE_HW_CLI_GUI
#define      HW_CLI_GUI_WIDTH       80
#define      HW_CLI_GUI_HEIGHT      24

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    2048
#define      HW_LOG_LIST_BUF_MAX    4096

#define _USE_HW_SWTIMER
#define      HW_SWTIMER_MAX_CH      8

#define _USE_HW_RTC
#define      HW_RTC_BOOT_MODE       RTC_BKP_DR3
#define      HW_RTC_RESET_BITS      RTC_BKP_DR4

#define _USE_HW_ADC                 
#define      HW_ADC_MAX_CH          ADC_PIN_MAX

#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH         GPIO_PIN_MAX

#define _USE_HW_PWM
#define      HW_PWM_MAX_CH          8

#define _USE_HW_SD
#define      HW_SD_EMMC             0

#define _USE_HW_I2C
#define      HW_I2C_MAX_CH          2

#define _USE_HW_SPI
#define      HW_SPI_MAX_CH          1

#define _USE_HW_CAN
#define      HW_CAN_MAX_CH          1
#define      HW_CAN_MSG_RX_BUF_MAX  32

#define _USE_HW_FLASH
#define      HW_FLASH_ADDR          0x8000000
#define      HW_FLASH_SIZE          (2 * 1024 * 1024)

#define _USE_HW_NEOPIXEL
#define      HW_NEOPIXEL_MAX_CH     1
#define      HW_NEOPIXEL_MAX_COUNT	1
#define      HW_NEOPIXEL_0  				0

#define _USE_HW_THREAD
#define      HW_THREAD_MAX_CNT      3

#define _HW_DEF_THREAD_PRI     			osPriorityNormal
#define _HW_DEF_THREAD_STACK   			2048


typedef enum
{
  GPIO_PIN_MAX = 0,
} GpioPinName_t;

typedef enum
{
  ADC1_1_location_X = 0,
  ADC1_2_location_Y,
  ADC1_3,
  ADC1_4,
  ADC1_6,
  CPU_TEMP,
  ADC_PIN_MAX
} AdcPinName_t;

typedef enum
{
  I2C_DEVICE_1 = 0,
  I2C_DEVICE_2,
  I2C_MAX
} I2C_t;

#endif
