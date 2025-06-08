/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "ap_def.h"
#include "hw_def.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef hlpuart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define UART_MAX_CH         HW_UART_MAX_CH
/* USER CODE END Private defines */

void MX_LPUART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
bool     uartInit(void);
bool     uartDeInit(void);
bool     uartIsInit(void);
bool     uartOpen(uint8_t ch, uint32_t baud);
bool     uartClose(uint8_t ch);
uint32_t uartAvailable(uint8_t ch);
bool     uartFlush(uint8_t ch);
uint8_t  uartRead(uint8_t ch);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint32_t uartPrintf(uint8_t ch, const char *fmt, ...);
uint32_t uartGetBaud(uint8_t ch);
uint32_t uartGetRxCnt(uint8_t ch);
uint32_t uartGetTxCnt(uint8_t ch);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

