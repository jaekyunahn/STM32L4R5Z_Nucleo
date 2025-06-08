#include "bsp.h"

void bspInit(void)
{
  dmaInit();
}

uint32_t millis(void)
{
  return HAL_GetTick();
}

void delay(uint32_t ms)
{
#ifdef _USE_HW_RTOS
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
    osDelay(ms);
  }
  else
  {
    HAL_Delay(ms);
  }
#else
  HAL_Delay(ms);
#endif
}

void dmaInit(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();
}