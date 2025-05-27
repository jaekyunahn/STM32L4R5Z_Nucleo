#ifndef HW_H_
#define HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#include "cli.h"
#include "cli_gui.h"
#include "util.h"
//#include "assert.h"
#include "qbuffer.h"
#include "thread.h"
//
#include "log.h"
#include "swtimer.h"

#include "rtc.h"

#include "reset.h"
#include "fault.h"
//
//#include "dma.h"
//#include "gpio.h"
//#include "uart.h"
//#include "pwm.h"
//#include "sd.h"
//#include "spi.h"
//#include "i2c.h"
//#include "adc.h"
//#include "usb.h"
//#include "cdc.h"
//
//#include "ws2812.h"

#include "adc.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "usb_otg.h"
#include "gpio.h"

#include "led.h"

bool hwInit(void);


#ifdef __cplusplus
}
#endif

#endif
