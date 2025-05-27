/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 6;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = ENABLE;
  hadc1.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_8;
  hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_3;
  hadc1.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc1.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_24CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
    PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
    PeriphClkInit.PLLSAI1.PLLSAI1M = 2;
    PeriphClkInit.PLLSAI1.PLLSAI1N = 25;
    PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV4;
    PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* ADC1 clock enable */
    __HAL_RCC_ADC_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN1
    PC1     ------> ADC1_IN2
    PC2     ------> ADC1_IN3
    PC3     ------> ADC1_IN4
    PA1     ------> ADC1_IN6
    PA3     ------> ADC1_IN8
    PC4     ------> ADC1_IN13
    PC5     ------> ADC1_IN14
    PB1     ------> ADC1_IN16
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel2;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN1
    PC1     ------> ADC1_IN2
    PC2     ------> ADC1_IN3
    PC3     ------> ADC1_IN4
    PA1     ------> ADC1_IN6
    PA3     ------> ADC1_IN8
    PC4     ------> ADC1_IN13
    PC5     ------> ADC1_IN14
    PB1     ------> ADC1_IN16
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

#define NAME_DEF(x) x, #x
#define lock()      xSemaphoreTake(mutex_lock, portMAX_DELAY);
#define unLock()    xSemaphoreGive(mutex_lock);

typedef struct
{
  ADC_HandleTypeDef *p_hadc;
  uint32_t           channel;
  uint32_t           rank;
  AdcPinName_t       pin_name;
  const char        *p_name;
} adc_tbl_t;

static void cliAdc(cli_args_t *args);


static SemaphoreHandle_t mutex_lock;
static bool              is_init = false;
static uint16_t          adc_data[ADC_MAX_CH];


static const adc_tbl_t adc_tbl[ADC_MAX_CH] =
{
  {&hadc1, ADC_CHANNEL_1,  ADC_REGULAR_RANK_1,  NAME_DEF(ADC1_1_location_X)           },
  {&hadc1, ADC_CHANNEL_2,  ADC_REGULAR_RANK_2,  NAME_DEF(ADC1_2_location_Y)           },
  {&hadc1, ADC_CHANNEL_3,  ADC_REGULAR_RANK_3,  NAME_DEF(ADC1_3)           },
  {&hadc1, ADC_CHANNEL_4,  ADC_REGULAR_RANK_4,  NAME_DEF(ADC1_4)           },
  {&hadc1, ADC_CHANNEL_5,  ADC_REGULAR_RANK_5,  NAME_DEF(ADC1_6)           },
  {&hadc1, ADC_CHANNEL_6,  ADC_REGULAR_RANK_6,  NAME_DEF(CPU_TEMP)           },
};

bool adcInit(void)
{
  bool ret = true;

  __HAL_RCC_DMA1_CLK_ENABLE();

  for (int i = 0; i < ADC_MAX_CH; i++)
  {
    assert_param(i == (int)adc_tbl[i].pin_name);
  }

  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_data[0], ADC_MAX_CH) != HAL_OK)
  {
    ret = false;
  }

  is_init = ret;

  logPrintf("[%s] adcInit()\n", is_init ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");

  cliAdd("adc", cliAdc);

  return ret;
}

bool adcIsInit(void)
{
  return is_init;
}

int32_t adcRead(uint8_t ch)
{
  assert_param(ch < ADC_MAX_CH);

  return adc_data[ch];
}

int32_t adcRead8(uint8_t ch)
{
  return adcRead(ch) >> 4;
}

int32_t adcRead10(uint8_t ch)
{
  return adcRead(ch) >> 2;
}

int32_t adcRead12(uint8_t ch)
{
  return adcRead(ch) >> 0;
}

int32_t adcRead16(uint8_t ch)
{
  return adcRead(ch) << 4;
}

uint8_t adcGetRes(uint8_t ch)
{
  return 12;
}

float adcReadVoltage(uint8_t ch)
{
  return adcConvVoltage(ch, adcRead(ch));
}

float adcConvVoltage(uint8_t ch, uint32_t adc_value)
{
  float ret = 0;

  switch (ch)
  {
    default:
      ret = ((float)adc_value * 3.3f) / (4095.f);
      break;
  }

  return ret;
}

//
//  ADC reset >> 계획만 해둠
//
bool adcReset(void)
{
  return false;
}

//
//  adc 먹통현상 해결위한 코드 >> 계획만 해둠
//
void adcWatchdogUpdate(void)
{

}

void cliAdc(cli_args_t *args)
{
  bool ret = false;
  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    cliPrintf("adc init : %d\n", is_init);
    cliPrintf("adc res  : %d\n", adcGetRes(0));
    for (int i = 0; i < ADC_MAX_CH; i++)
    {
      cliPrintf("%02d. %-32s : %04d\n", i, adc_tbl[i].p_name, adcRead(i));
    }

    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "show") == true)
  {
    cliGui()->showCursor(false);
    while (cliKeepLoop())
    {
      for (int i = 0; i < ADC_MAX_CH; i++)
      {
        cliPrintf("%02d. %-32s : %04d \n", i, adc_tbl[i].p_name, adcRead(i));
      }
      delay(50);
      cliPrintf("\x1B[%dA", ADC_MAX_CH);
    }
    cliPrintf("\x1B[%dB", ADC_MAX_CH);
    cliGui()->showCursor(true);
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "show") && args->isStr(1, "vol"))
  {
    cliGui()->showCursor(false);
    while (cliKeepLoop())
    {
      for (int i = 0; i < ADC_MAX_CH; i++)
      {
        float adc_data;

        adc_data = adcReadVoltage(i);

        cliPrintf("%02d. %-32s : %d.%02dV \n", i, adc_tbl[i].p_name, (int)adc_data, (int)(adc_data * 100) % 100);
      }
      delay(50);
      cliPrintf("\x1B[%dA", ADC_MAX_CH);
    }
    cliPrintf("\x1B[%dB", ADC_MAX_CH);
    cliGui()->showCursor(true);
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "reset") == true)
  {
    adcReset();
    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("adc info\n");
    cliPrintf("adc show\n");
    cliPrintf("adc show vol\n");
    cliPrintf("adc reset\n");
  }
}






/* USER CODE END 1 */
