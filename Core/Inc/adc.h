/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "ap_def.h"
#include "hw_def.h"
/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
#define ADC_MAX_CH    HW_ADC_MAX_CH
/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
bool    adcInit(void);
bool    adcIsInit(void);
int32_t adcRead(uint8_t ch);
int32_t adcRead8(uint8_t ch);
int32_t adcRead10(uint8_t ch);
int32_t adcRead12(uint8_t ch);
int32_t adcRead16(uint8_t ch);
uint8_t adcGetRes(uint8_t ch);
float   adcReadVoltage(uint8_t ch);
float   adcConvVoltage(uint8_t ch, uint32_t adc_value);
bool    adcReset(void);
void    adcWatchdogUpdate(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

