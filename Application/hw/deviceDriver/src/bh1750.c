#include "bh1750.h"

static void cliCmd(cli_args_t *args);

static bool is_init = false;
static bool is_found = false;
static uint8_t i2c_ch = I2C_DEVICE_1;
static uint8_t i2c_addr = 0x23;

void bh1750Init(void)
{
  bool ret = true;  

  assert_param(i2cIsInit());

  if (i2cIsBegin(I2C_DEVICE_1) == false)
  {
    ret = i2cBegin(I2C_DEVICE_1, 100);
    assert_param(ret);
    if (ret == false)
      logPrintf("     i2cBegin() Fail\n");
  }

  if (ret)
  {
    ret = bh1750FindChip();
    // if (ret)
    //   logPrintf("     Found bh1750\n");
    // else
    //   logPrintf("     Not Found Chip\n");

    is_found = ret;
  }

  ret = bh1750StartUp();
  // if (ret)
  //   logPrintf("     StartUp bh1750\n");
  // else
  //   logPrintf("     StartUp Fail\n");

  is_init = ret;

  logPrintf("[%s] bh1750Init()\n", is_init ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");

  cliAdd("bh1750", cliCmd);
  return ret;
}

bool bh1750IsInit(void)
{
  return is_init;
}

bool bh1750StartUp(void)
{
  bool ret;
  uint8_t cmd;

  cmd = 0x01;
  ret = i2cWriteData(i2c_ch, i2c_addr, &cmd, 1, 50);
  if (!ret) return false;

  cmd = 0x07;
  ret = i2cWriteData(i2c_ch, i2c_addr, &cmd, 1, 50);
  if (!ret) return false;

  cmd = 0x10;
  ret = i2cWriteData(i2c_ch, i2c_addr, &cmd, 1, 50);
  if (!ret) return false;

  return true;
}

bool bh1750FindChip(void)
{
  bool ret;
  uint8_t data;
  ret = i2cReadData(i2c_ch, i2c_addr, &data, 1, 50);
  return ret;
}

bool bh1750ReadLux(float *lux)
{
  uint8_t buf[2];
  bool ret;
  ret = i2cReadData(i2c_ch, i2c_addr, buf, 2, 50);
  if (!ret) 
    return false;
  uint16_t raw = ((uint16_t)buf[0] << 8) | buf[1];
  *lux = (float)raw / 1.2f; 
  return true;
}


void cliCmd(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "read") == true)
  {
    //bh1750ReadLux
    float tmp;
    
    cliGui()->showCursor(false);
    while(cliKeepLoop())
    {
      bh1750ReadLux(&tmp);
      cliPrintf("bh1750ReadLux=%5d\n",(uint16_t)tmp);

      delay(100);
      cliGui()->moveUp(1);
    }
    cliGui()->moveDown(1);
    cliGui()->showCursor(true);

    ret = true;
  }

}











