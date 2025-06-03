/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    i2c.c
 * @brief   This file provides code for the configuration
 *          of the I2C instances.
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
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x30A175AB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}
/* I2C2 init function */
void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x30A175AB;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
    PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**I2C2 GPIO Configuration
    PF0     ------> I2C2_SDA
    PF1     ------> I2C2_SCL
    PF2     ------> I2C2_SMBA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* I2C2 clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();
  /* USER CODE BEGIN I2C2_MspInit 1 */

  /* USER CODE END I2C2_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();

    /**I2C2 GPIO Configuration
    PF0     ------> I2C2_SDA
    PF1     ------> I2C2_SCL
    PF2     ------> I2C2_SMBA
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_2);

  /* USER CODE BEGIN I2C2_MspDeInit 1 */

  /* USER CODE END I2C2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

#include "cli.h"

#define lock()   xSemaphoreTake(mutex_lock, portMAX_DELAY);
#define unLock() xSemaphoreGive(mutex_lock);

static uint32_t i2cGetTimming(uint32_t freq_khz);
static void     delayUs(uint32_t us);
static void     cliI2C(cli_args_t *args);


static uint32_t i2c_timeout[I2C_MAX_CH];
static uint32_t i2c_errcount[I2C_MAX_CH];
static uint32_t i2c_freq[I2C_MAX_CH];

static bool is_init = false;
static bool is_begin[I2C_MAX_CH];

static SemaphoreHandle_t mutex_lock;

typedef struct
{
  I2C_TypeDef       *p_i2c;
  I2C_HandleTypeDef *p_hi2c;

  GPIO_TypeDef *scl_port;
  int           scl_pin;

  GPIO_TypeDef *sda_port;
  int           sda_pin;
} i2c_tbl_t;

static const i2c_tbl_t i2c_tbl[I2C_MAX_CH] =
{
  //                       SCL                 SDA
  {I2C1, &hi2c1, GPIOB, GPIO_PIN_8, GPIOB, GPIO_PIN_9},
  {I2C2, &hi2c2, GPIOF, GPIO_PIN_1, GPIOF, GPIO_PIN_0},
};

bool i2cInit(void)
{
  uint32_t i;


  mutex_lock = xSemaphoreCreateMutex();
  for (i = 0; i < I2C_MAX_CH; i++)
  {
    i2c_timeout[i]  = 10;
    i2c_errcount[i] = 0;
    is_begin[i]     = false;
  }

#ifdef _USE_HW_CLI
  cliAdd("i2c", cliI2C);
#endif

  is_init = true;
  logPrintf("[%s] i2cInit()\n", is_init ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");
  
  return true;
}

bool i2cIsInit(void)
{
  return is_init;
}

bool i2cBegin(uint8_t ch, uint32_t freq_khz)
{
  bool ret = false;

  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  if (ch >= I2C_MAX_CH)
  {
    return false;
  }


  switch (ch)
  {
    case _DEF_I2C1:
    case _DEF_I2C2:
      i2c_freq[ch] = freq_khz;

      i2cReset(ch);

      HAL_I2C_DeInit(p_handle);
      if (HAL_I2C_Init(p_handle) != HAL_OK)
      {
      }

      /* Enable the Analog I2C Filter */
      HAL_I2CEx_ConfigAnalogFilter(p_handle, I2C_ANALOGFILTER_ENABLE);

      /* Configure Digital filter */
      HAL_I2CEx_ConfigDigitalFilter(p_handle, 0);

      ret          = true;
      is_begin[ch] = true;
      break;
  }

  return ret;
}

uint32_t i2cGetTimming(uint32_t freq_khz)
{
  uint32_t ret;

  switch (freq_khz)
  {
    case 100:
      ret = 0x103089FF;
      break;

    case 400:
      ret = 0x00702991;
      break;

    default:
      ret = 0x00702991;
      break;
  };

  return ret;
}

bool i2cIsBegin(uint8_t ch)
{
  return is_begin[ch];
}

void i2cReset(uint8_t ch)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  const i2c_tbl_t *p_pin = &i2c_tbl[ch];


  GPIO_InitStruct.Pin   = p_pin->scl_pin;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(p_pin->scl_port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin  = p_pin->sda_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(p_pin->sda_port, &GPIO_InitStruct);


  HAL_GPIO_WritePin(p_pin->scl_port, p_pin->scl_pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(p_pin->sda_port, p_pin->sda_pin, GPIO_PIN_SET);
  delayUs(5);

  for (int i = 0; i < 9; i++)
  {
    HAL_GPIO_WritePin(p_pin->scl_port, p_pin->scl_pin, GPIO_PIN_RESET);
    delayUs(5);
    HAL_GPIO_WritePin(p_pin->scl_port, p_pin->scl_pin, GPIO_PIN_SET);
    delayUs(5);
  }

  HAL_GPIO_WritePin(p_pin->scl_port, p_pin->scl_pin, GPIO_PIN_RESET);
  delayUs(5);
  HAL_GPIO_WritePin(p_pin->sda_port, p_pin->sda_pin, GPIO_PIN_RESET);
  delayUs(5);

  HAL_GPIO_WritePin(p_pin->scl_port, p_pin->scl_pin, GPIO_PIN_SET);
  delayUs(5);
  HAL_GPIO_WritePin(p_pin->sda_port, p_pin->sda_pin, GPIO_PIN_SET);
}

bool i2cIsDeviceReady(uint8_t ch, uint8_t dev_addr)
{
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;
  assert_param(is_begin[ch]);

  if (HAL_I2C_IsDeviceReady(p_handle, dev_addr << 1, 10, 10) == HAL_OK)
  {
    __enable_irq();
    return true;
  }

  return false;
}

bool i2cRecovery(uint8_t ch)
{
  bool ret;

  i2cReset(ch);

  ret = i2cBegin(ch, i2c_freq[ch]);

  return ret;
}

bool i2cReadByte(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t timeout)
{
  return i2cReadBytes(ch, dev_addr, reg_addr, p_data, 1, timeout);
}

bool i2cReadBytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Mem_Read(p_handle, (uint16_t)(dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, p_data, length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool i2cReadA16Bytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Mem_Read(p_handle, (uint16_t)(dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_16BIT, p_data, length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool i2cReadData(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Master_Receive(p_handle, (uint16_t)(dev_addr << 1), p_data, (uint16_t)length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool i2cWriteByte(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t data, uint32_t timeout)
{
  return i2cWriteBytes(ch, dev_addr, reg_addr, &data, 1, timeout);
}

bool i2cWriteBytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Mem_Write(p_handle, (uint16_t)(dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, p_data, length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool i2cWriteA16Bytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Mem_Write(p_handle, (uint16_t)(dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_16BIT, p_data, length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool i2cWriteData(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool               ret;
  HAL_StatusTypeDef  i2c_ret;
  I2C_HandleTypeDef *p_handle = i2c_tbl[ch].p_hi2c;

  assert_param(ch < I2C_MAX_CH);
  assert_param(is_begin[ch]);

  lock();
  i2c_ret = HAL_I2C_Master_Transmit(p_handle, (uint16_t)(dev_addr << 1), p_data, length, timeout);
  unLock();

  if (i2c_ret == HAL_OK)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

void i2cSetTimeout(uint8_t ch, uint32_t timeout)
{
  i2c_timeout[ch] = timeout;
}

uint32_t i2cGetTimeout(uint8_t ch)
{
  return i2c_timeout[ch];
}

void i2cClearErrCount(uint8_t ch)
{
  i2c_errcount[ch] = 0;
}

uint32_t i2cGetErrCount(uint8_t ch)
{
  return i2c_errcount[ch];
}

void delayUs(uint32_t us)
{
  volatile uint32_t i;

  for (i = 0; i < us * 1000; i++)
  {
  }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  UNUSED(hi2c);
}

void cliI2C(cli_args_t *args)
{
  bool ret = true;
  bool i2c_ret;

  uint8_t  print_ch;
  uint8_t  ch;
  uint16_t dev_addr;
  uint16_t reg_addr;
  uint16_t length;

  uint32_t i;
  uint8_t  i2c_data[128];
  uint32_t pre_time;

  if (args->argc == 2)
  {
    print_ch = (uint16_t)args->getData(1);

    print_ch  = constrain(print_ch, 1, I2C_MAX_CH);
    print_ch -= 1;

    if (args->isStr(0, "scan") == true)
    {
      if (i2cIsBegin(print_ch) == true)
      {
        for (i = 0x00; i <= 0x7F; i++)
        {
          if (i2cIsDeviceReady(print_ch, i) == true)
          {
            cliPrintf("I2C CH%d Addr 0x%02X : OK\n", print_ch + 1, i);
          }
          else if (i == 0x4C)
          {
            cliPrintf("I2C CH%d Addr 0x%02X : Failed\n", print_ch + 1, i);
          }
        }
      }
      else
      {
        cliPrintf("i2c ch%d is not begin\n", print_ch + 1);
      }
    }
    else if (args->isStr(0, "begin") == true)
    {
      i2c_ret = i2cBegin(print_ch, 400);
      if (i2c_ret == true)
      {
        cliPrintf("I2C CH%d Begin OK\n", print_ch + 1);
      }
      else
      {
        cliPrintf("I2C CH%d Begin Fail\n", print_ch + 1);
      }
    }
  }
  else if (args->argc == 5)
  {
    print_ch = (uint16_t)args->getData(1);
    print_ch = constrain(print_ch, 1, I2C_MAX_CH);

    dev_addr = (uint16_t)args->getData(2);
    reg_addr = (uint16_t)args->getData(3);
    length   = (uint16_t)args->getData(4);
    ch       = print_ch - 1;

    if (args->isStr(0, "read") == true)
    {
      for (i = 0; i < length; i++)
      {
        i2c_ret = i2cReadByte(ch, dev_addr, reg_addr + i, i2c_data, 100);

        if (i2c_ret == true)
        {
          cliPrintf("%d I2C - 0x%02X : 0x%02X\n", print_ch, reg_addr + i, i2c_data[0]);
        }
        else
        {
          cliPrintf("%d I2C - Fail \n", print_ch);
          break;
        }
      }
    }
    else if (args->isStr(0, "write") == true)
    {
      pre_time = millis();
      i2c_ret  = i2cWriteByte(ch, dev_addr, reg_addr, (uint8_t)length, 100);

      if (i2c_ret == true)
      {
        cliPrintf("%d I2C - 0x%02X : 0x%02X, %d ms\n", print_ch, reg_addr, length, millis() - pre_time);
      }
      else
      {
        cliPrintf("%d I2C - Fail \n", print_ch);
      }
    }
    else
    {
      ret = false;
    }
  }
  else if (args->argc == 4)
  {
    print_ch = (uint16_t)args->getData(1);
    print_ch = constrain(print_ch, 1, I2C_MAX_CH);

    dev_addr = (uint16_t)args->getData(2);
    length   = (uint16_t)args->getData(3);
    ch       = print_ch - 1;

    if (args->isStr(0, "read_d") == true)
    {
      uint8_t read_buf[length];

      i2c_ret = i2cReadData(ch, dev_addr, read_buf, length, 100);

      if (i2c_ret == true)
      {
        for (int i = 0; i < length; i++)
          cliPrintf("%d I2C - 0x%02X : 0x%02X\n", print_ch, i, read_buf[i]);
      }
      else
      {
        cliPrintf("%d I2C - Fail \n", print_ch);
      }
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }

  if (ret == false)
  {
    cliPrintf("i2c begin ch[1~%d]\n", I2C_MAX_CH);
    cliPrintf("i2c scan  ch[1~%d]\n", I2C_MAX_CH);
    cliPrintf("i2c read  ch dev_addr reg_addr length\n");
    cliPrintf("i2c write ch dev_addr reg_addr data\n");
    cliPrintf("i2c read_d ch dev_addr length\n");
  }
}

/* USER CODE END 1 */
