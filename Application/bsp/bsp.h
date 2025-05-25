#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mw.h"
#include "hw_def.h"
#include "def.h"
#include "stm32l4xx_hal.h"

void bspInit(void);
uint32_t millis(void);
void delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif
