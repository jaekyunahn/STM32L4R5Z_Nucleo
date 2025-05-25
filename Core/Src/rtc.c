/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "log.h"
#include "cli.h"
#include <time.h>

static void cliRtc(cli_args_t *args);
static bool is_init = false;
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  is_init = true;
  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
bool rtcInit(void)
{
  bool ret = is_init;

  logPrintf("[%s] rtcInit()\n", ret ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");

#ifdef _USE_HW_CLI
  cliAdd("rtc", cliRtc);
#endif
  return ret;
}

bool rtcGetInfo(rtc_info_t *rtc_info)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_info->time.hours = sTime.Hours;
  rtc_info->time.minutes = sTime.Minutes;
  rtc_info->time.seconds = sTime.Seconds;

  rtc_info->date.year = sDate.Year;
  rtc_info->date.month = sDate.Month;
  rtc_info->date.day = sDate.Date;

  return true;
}

bool rtcGetTime(rtc_time_t *rtc_time)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_time->hours = sTime.Hours;
  rtc_time->minutes = sTime.Minutes;
  rtc_time->seconds = sTime.Seconds;

  return true;
}

bool rtcGetDate(rtc_date_t *rtc_date)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_date->year = sDate.Year;
  rtc_date->month = sDate.Month;
  rtc_date->day = sDate.Date;


  struct tm  timeinfo;

  memset(&timeinfo, 0, sizeof(timeinfo));
  timeinfo.tm_year  = (2000 + sDate.Year) - 1900;
  timeinfo.tm_mon   = sDate.Month - 1;
  timeinfo.tm_mday  = sDate.Date;
  timeinfo.tm_hour  = sTime.Hours;
  timeinfo.tm_min   = sTime.Minutes;
  timeinfo.tm_sec   = sTime.Seconds;

  mktime(&timeinfo);

  rtc_date->week = timeinfo.tm_wday;

  return true;
}

bool rtcSetTime(rtc_time_t *rtc_time)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  sTime.Hours = rtc_time->hours;
  sTime.Minutes = rtc_time->minutes;
  sTime.Seconds = rtc_time->seconds;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  return true;
}

bool rtcSetDate(rtc_date_t *rtc_date)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  sDate.Year = rtc_date->year;
  sDate.Month = rtc_date->month;
  sDate.Date = rtc_date->day;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  return true;
}

// void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
// {
//   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
//   if(rtcHandle->Instance==RTC)
//   {
//     PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
//     PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
//     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     __HAL_RCC_RTC_ENABLE();
//   }
// }

bool rtcSetReg(uint32_t index, uint32_t data)
{
  if (IS_RTC_BKP(index))
  {
    HAL_RTCEx_BKUPWrite(&hrtc, index, data);
    return true;
  }
  else
  {
    return false;
  }
}

bool rtcGetReg(uint32_t index, uint32_t *p_data)
{
  if (IS_RTC_BKP(index))
  {
    *p_data = HAL_RTCEx_BKUPRead(&hrtc, index);
    return true;
  }
  else
  {
    return false;
  }
}

// void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
// {

//   if(rtcHandle->Instance==RTC)
//   {
//     __HAL_RCC_RTC_DISABLE();
//   }
// }

void cliRtc(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("is_init : %d\n", is_init);
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "get") && args->isStr(1, "info"))
  {
    rtc_info_t rtc_info;

    while(cliKeepLoop())
    {
      rtcGetInfo(&rtc_info);

      cliPrintf("Y:%02d M:%02d D:%02d, H:%02d M:%02d S:%02d\n",
                rtc_info.date.year,
                rtc_info.date.month,
                rtc_info.date.day,
                rtc_info.time.hours,
                rtc_info.time.minutes,
                rtc_info.time.seconds);
      delay(1000);
    }
    ret = true;
  }

  if (args->argc == 5 && args->isStr(0, "set") && args->isStr(1, "time"))
  {
    rtc_time_t rtc_time;

    rtc_time.hours = args->getData(2);
    rtc_time.minutes = args->getData(3);
    rtc_time.seconds = args->getData(4);

    rtcSetTime(&rtc_time);
    cliPrintf("H:%02d M:%02d S:%02d\n",
              rtc_time.hours,
              rtc_time.minutes,
              rtc_time.seconds);
    ret = true;
  }

  if (args->argc == 5 && args->isStr(0, "set") && args->isStr(1, "date"))
  {
    rtc_date_t rtc_date;

    rtc_date.year = args->getData(2);
    rtc_date.month = args->getData(3);
    rtc_date.day = args->getData(4);

    rtcSetDate(&rtc_date);
    cliPrintf("Y:%02d M:%02d D:%02d\n", rtc_date.year, rtc_date.month, rtc_date.day);
    ret = true;
  }


  if (ret == false)
  {
    cliPrintf("rtc info\n");
    cliPrintf("rtc get info\n");
    cliPrintf("rtc set time [h] [m] [s]\n");
    cliPrintf("rtc set date [y] [m] [d]\n");
  }
}

/* USER CODE END 1 */
