#include "bno055.h"

static void cliCmd(cli_args_t *args);

static bool    is_init  = false;
static bool    is_found = false;
static uint8_t i2c_ch   = I2C_DEVICE_1;
static uint8_t i2c_addr = 0x29;

void bno055Init(void)
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
    ret = bno055FindChip();
    if (ret)
      logPrintf("     Found bno055\n");
    else
      logPrintf("     Not Found Chip\n");

    is_found = ret;
  }

  ret = bno055StartUp();
  if (ret)
    logPrintf("     StartUp bno055\n");
  else
    logPrintf("     StartUp Fail\n");

  is_init = ret;

  logPrintf("[%s] bno055Init()\n", is_init ? "\033[32mOK\033[0m" : "\033[31mNG\033[0m");

  cliAdd("bno055", cliCmd);
  return ret;
}

bool bno055IsInit(void)
{
  return is_init;
}

bool bno055StartUp(void)
{
  bool ret;

  // 1. 소프트 리셋: SYS_TRIGGER = 0x20
  uint8_t resetCmd[] = {0x3F, 0x20};
  ret = i2cWriteData(i2c_ch, i2c_addr, &resetCmd, 2, 50);
  if (!ret)
    return false;

  // 2. 리셋 후 안정화 대기 (650ms 이상)
  delay(1000); // 최소 650ms

  // 3. CONFIG 모드로 전환: OPR_MODE = 0x00
  uint8_t configMode[] = {0x3D, 0x00};
  ret = i2cWriteData(i2c_ch, i2c_addr, &configMode, 2, 50);
  if (!ret)
    return false;


  // 4. 외부 크리스탈 사용 설정: SYS_TRIGGER = 0x80
  // ※ 외부 크리스탈이 연결된 경우에만
  uint8_t extCrystal[] = {0x3F, 0x80};
  ret = i2cWriteData(i2c_ch, i2c_addr, &extCrystal, 2, 50);
  if (!ret)
    return false;

  // 5. 다시 CONFIG 모드 안정화 대기
  delay(200); // 내부 준비 시간

  // 6. NDOF 모드로 전환: OPR_MODE = 0x0C
  uint8_t ndofMode[] = {0x3D, 0x0C};
  ret = i2cWriteData(i2c_ch, i2c_addr, &ndofMode, 2, 50);
  if (!ret)
    return false;

  // 7. 모드 변경 후 내부 센서 안정화 대기
  delay(200);

  uint8_t startAddr = 0x3D;
  ret = i2cWriteData(i2c_ch, i2c_addr, &startAddr, 1, 50);
  if (!ret)
    return false;

  ret = i2cReadData(i2c_ch, i2c_addr, &startAddr, 1, 50);
  if (!ret)
    return false;

logPrintf("[BNO_055] mode=%d\n", startAddr);

  return true;
}

bool bno055FindChip(void)
{
  bool    ret;
  uint8_t data;
  ret = i2cReadData(i2c_ch, i2c_addr, &data, 1, 50);
  return ret;
}

bool bno055ReadData(bno_055_data_t *data)
{
  uint8_t startAddr      = 0x08;
  uint8_t sensorData[18] = {0};
    bool ret = false;
  ret = i2cWriteData(i2c_ch, i2c_addr, &startAddr, 1, 50); // 읽기 시작 주소 지정
  if(ret == false)
  {
    logPrintf("address write fail\n");
  }                                                   
  
  ret = i2cReadData(i2c_ch, i2c_addr, &sensorData, 18, 50);
  if(ret == false)
  {
    logPrintf("data read fail\n");
  }                           

  // 데이터 파싱
  int16_t ax = (sensorData[1] << 8) | sensorData[0];
  int16_t ay = (sensorData[3] << 8) | sensorData[2];
  int16_t az = (sensorData[5] << 8) | sensorData[4];

  int16_t mx = (sensorData[7] << 8) | sensorData[6];
  int16_t my = (sensorData[9] << 8) | sensorData[8];
  int16_t mz = (sensorData[11] << 8) | sensorData[10];

  int16_t gx = (sensorData[13] << 8) | sensorData[12];
  int16_t gy = (sensorData[15] << 8) | sensorData[14];
  int16_t gz = (sensorData[17] << 8) | sensorData[16];

  // 가속도 (g 단위)
  float ax_g = (float)ax / 1000.0f;
  float ay_g = (float)ay / 1000.0f;
  float az_g = (float)az / 1000.0f;

  // 자기장 (µT)
  float mx_uT = (float)mx * 1.0f;

  // 자이로 (deg/s)
  float gx_dps = (float)gx / 16.0f;
  float gy_dps = (float)gy / 16.0f;
  float gz_dps = (float)gz / 16.0f;

  return true;
}

void cliCmd(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "read") == true)
  {
    // bh1750ReadLux
    bno_055_data_t tmp;

    cliGui()->showCursor(false);
    while (cliKeepLoop())
    {
      bno055ReadData(&tmp);
      cliPrintf("bno055Read ax=%3d,ay=%3d,az=%3d,mx=%3d,gx=%3d,gy=%3d,gz=%3d\n", (int16_t)tmp.ax_g, (int16_t)tmp.ay_g, (int16_t)tmp.az_g,(int16_t)tmp.mx_uT,(int16_t)tmp.gx_dps,(int16_t)tmp.gy_dps,(int16_t)tmp.gz_dps);

      delay(100);
      cliGui()->moveUp(1);
    }
    cliGui()->moveDown(1);
    cliGui()->showCursor(true);

    ret = true;
  }
}
