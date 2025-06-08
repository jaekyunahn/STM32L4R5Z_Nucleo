/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sdmmc.c
  * @brief   This file provides code for the configuration
  *          of the SDMMC instances.
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
#include "sdmmc.h"

/* USER CODE BEGIN 0 */
static bool is_init = false;
static bool is_detected = false;
static volatile bool is_rx_done = false;
static volatile bool is_tx_done = false;
static uint8_t is_try = 0;
static sd_state_t sd_state = SDCARD_IDLE;

// static SD_HandleTypeDef hsd;


#ifdef _USE_HW_CLI
static void cliSd(cli_args_t *args);
#endif

/* USER CODE END 0 */

SD_HandleTypeDef hsd1;

/* SDMMC1 init function */

void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 11;
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_DISABLE;
  if (HAL_SD_Init(&hsd1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SDMMC1_Init 2 */
  is_init = true;
  /* USER CODE END SDMMC1_Init 2 */

}

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(sdHandle->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */

  /* USER CODE END SDMMC1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SDMMC1;
    PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* SDMMC1 clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN SDMMC1_MspInit 1 */

  /* USER CODE END SDMMC1_MspInit 1 */
  }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle)
{

  if(sdHandle->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspDeInit 0 */

  /* USER CODE END SDMMC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC1_CLK_DISABLE();

    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10     ------> SDMMC1_D2
    PC11     ------> SDMMC1_D3
    PC12     ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

  /* USER CODE BEGIN SDMMC1_MspDeInit 1 */

  /* USER CODE END SDMMC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


bool sdInit(void)
{
  bool ret = is_init;

  logPrintf("[%s] sdInit()\n", ret ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");   

#ifdef _USE_HW_CLI
  cliAdd("sd", cliSd);
#endif

  return ret;
}

bool sdReInit(void)
{
  bool ret = false;

  HAL_SD_DeInit(&hsd1);
  if (HAL_SD_Init(&hsd1) == HAL_OK)
  {
    ret = true;
  }

  is_init = ret;

  return ret;
}

bool sdDeInit(void)
{
  bool ret = false;

  if (is_init == true)
  {
    is_init = false;

    if (HAL_SD_DeInit(&hsd1) == HAL_OK)
    {
      ret = true;
    }
  }

  return ret;
}

bool sdIsInit(void)
{
  return is_init;
}

bool sdIsDetected(void)
{
  return true;
}

sd_state_t sdUpdate(void)
{
  sd_state_t ret_state = SDCARD_IDLE;
  static uint32_t pre_time;

  switch(sd_state)
  {
    case SDCARD_IDLE:
      if (sdIsDetected() == true)
      {
        if (is_init)
        {
          sd_state = SDCARD_CONNECTED;
        }
        else
        {
          sd_state = SDCARD_CONNECTTING;
          pre_time = millis();
        }
      }
      else
      {
        is_init = false;
        sd_state  = SDCARD_DISCONNECTED;
        ret_state = SDCARD_DISCONNECTED;
      }
      break;

    case SDCARD_CONNECTTING:
      if (millis()-pre_time >= 100)
      {
        if (sdReInit())
        {
          sd_state  = SDCARD_CONNECTED;
          ret_state = SDCARD_CONNECTED;
        }

        else
        {
          sd_state = SDCARD_IDLE;
          is_try++;

          if (is_try >= 3)
          {
            sd_state = SDCARD_ERROR;
          }
        }
      }
      break;

    case SDCARD_CONNECTED:
      if (sdIsDetected() != true)
      {
        is_try = 0;
        sd_state = SDCARD_IDLE;
      }
      break;

    case SDCARD_DISCONNECTED:
      if (sdIsDetected() == true)
      {
        sd_state = SDCARD_IDLE;
      }
      break;

    case SDCARD_ERROR:
      break;
  }

  return ret_state;
}

bool sdGetInfo(sd_info_t *p_info)
{
  bool ret = false;
  sd_info_t *p_sd_info = (sd_info_t *)p_info;

  HAL_SD_CardInfoTypeDef card_info;


  if (is_init == true)
  {
    HAL_SD_GetCardInfo(&hsd1, &card_info);

    p_sd_info->card_type          = card_info.CardType;
    p_sd_info->card_version       = card_info.CardVersion;
    p_sd_info->card_class         = card_info.Class;
    p_sd_info->rel_card_Add       = card_info.RelCardAdd;
    p_sd_info->block_numbers      = card_info.BlockNbr;
    p_sd_info->block_size         = card_info.BlockSize;
    p_sd_info->log_block_numbers  = card_info.LogBlockNbr;
    p_sd_info->log_block_size     = card_info.LogBlockSize;
    p_sd_info->card_size          =  (uint32_t)((uint64_t)p_sd_info->block_numbers * (uint64_t)p_sd_info->block_size / (uint64_t)1024 / (uint64_t)1024);
    ret = true;
  }

  return ret;
}

bool sdIsBusy(void)
{
  bool is_busy;

  if (HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER )
  {
    is_busy = false;
  }
  else
  {
    is_busy = true;
  }

  return is_busy;
}

bool sdIsReady(uint32_t timeout)
{
  uint32_t pre_time;

  pre_time = millis();

  while(millis() - pre_time < timeout)
  {
    if (sdIsBusy() == false)
    {
      return true;
    }
  }

  return false;
}

bool sdReadBlocks(uint32_t block_addr, uint8_t *p_data, uint32_t num_of_blocks, uint32_t timeout_ms)
{
  bool ret = false;
  uint32_t pre_time;


  if (is_init == false) return false;


  is_rx_done = false;

  if(HAL_SD_ReadBlocks_DMA(&hsd1, (uint8_t *)p_data, block_addr, num_of_blocks) == HAL_OK)
  {

    pre_time = millis();
    while(is_rx_done == false)
    {
      if (millis()-pre_time >= timeout_ms)
      {
        break;
      }
    }
    while(sdIsBusy() == true)
    {
      if (millis()-pre_time >= timeout_ms)
      {
        is_rx_done = false;
        break;
      }
    }
    ret = is_rx_done;
  }
  if (ret == true)
  {

  }
  return ret;
}

bool sdWriteBlocks(uint32_t block_addr, uint8_t *p_data, uint32_t num_of_blocks, uint32_t timeout_ms)
{
  bool ret = false;
  uint32_t pre_time;

  if (is_init == false) return false;

  is_tx_done = false;

  if(HAL_SD_WriteBlocks_DMA(&hsd1, (uint8_t *)p_data, block_addr, num_of_blocks) == HAL_OK)
  {
    pre_time = millis();
    while(is_tx_done == false)
    {
      if (millis()-pre_time >= timeout_ms)
      {
        break;
      }
    }
    pre_time = millis();
    while(sdIsBusy() == true)
    {
      if (millis()-pre_time >= timeout_ms)
      {
        is_tx_done = false;
        break;
      }
    }
    ret = is_tx_done;
  }

  return ret;
}

bool sdEraseBlocks(uint32_t start_addr, uint32_t end_addr)
{
  bool ret = false;

  if (is_init == false) return false;

  if(HAL_SD_Erase(&hsd1, start_addr, end_addr) == HAL_OK)
  {
    ret = true;
  }

  return ret;
}

void SDMMC2_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hsd1);
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
  is_rx_done = true;
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
  is_tx_done = true;
}

void cliSd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    sd_info_t sd_info;

    cliPrintf("sd init      : %d\n", is_init);
    cliPrintf("sd connected : %d\n", is_detected);

    if (is_init == true)
    {
      if (sdGetInfo(&sd_info) == true)
      {
        cliPrintf("   card_type            : %d\n", sd_info.card_type);
        cliPrintf("   card_version         : %d\n", sd_info.card_version);
        cliPrintf("   card_class           : %d\n", sd_info.card_class);
        cliPrintf("   rel_card_Add         : %d\n", sd_info.rel_card_Add);
        cliPrintf("   block_numbers        : %d\n", sd_info.block_numbers);
        cliPrintf("   block_size           : %d\n", sd_info.block_size);
        cliPrintf("   log_block_numbers    : %d\n", sd_info.log_block_numbers);
        cliPrintf("   log_block_size       : %d\n", sd_info.log_block_size);
        cliPrintf("   card_size            : %d MB, %d.%d GB\n", sd_info.card_size, sd_info.card_size/1024, ((sd_info.card_size * 10)/1024) % 10);
      }
    }
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "read") == true)
  {
    uint32_t number;
    uint32_t buf[512/4];

    number = args->getData(1);

    if (sdReadBlocks(number, (uint8_t *)buf, 1, 100) == true)
    {
      for (int i=0; i<512/4; i++)
      {
        cliPrintf("%d:%04d : 0x%08X\n", number, i*4, buf[i]);
      }
    }
    else
    {
      cliPrintf("sdRead Fail\n");
    }

    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("sd info\n");

    if (is_init == true)
    {
      cliPrintf("sd read block_number\n");
    }
  }
}

/* USER CODE END 1 */
