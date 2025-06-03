#include "bno055.h"

static void cliCmd(cli_args_t *args);

static bool    is_init  = false;
static bool    is_found = false;
static uint8_t i2c_ch   = I2C_DEVICE_1;
static uint8_t i2c_addr = BNO055_I2C_ADDRESS;

uint8_t cal_data[23] = {
  // 예시 값: 이전에 저장해둔 데이터 삽입
  0x55,
  0xFC, 0xFF, 0x03, 0x00, 0xFD, 0xFF, // ACC offsets
  0xFD, 0xFF, 0x01, 0x00, 0x01, 0x00, // MAG offsets
  0xFE, 0xFF, 0x00, 0x00, 0x01, 0x00, // GYRO offsets
  0x2D, 0x00,                         // ACC radius
  0x2D, 0x00                          // MAG radius
};

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

  // 1. 소프트 리셋: SYS_TRIGGER = 0x20 >> datasheet : p.76
  uint8_t resetCmd[] = {0x3F, 0x20};
  ret = i2cWriteData(i2c_ch, i2c_addr, &resetCmd, 2, 1000);
  if (!ret)
    return false;

  // 2. 리셋 후 안정화 대기 (650ms 이상)
  delay(1000);

  // 3. CONFIG 모드로 전환: OPR_MODE = 0x00 >> datasheet : p.76
  uint8_t configMode[] = {0x3D, 0x00};
  ret = i2cWriteData(i2c_ch, i2c_addr, &configMode, 2, 1000);
  if (!ret)
    return false;

  // 4. 외부 크리스탈 사용 설정: SYS_TRIGGER = 0x80 ※ 외부 크리스탈이 연결된 경우에만 >> datasheet : p.76
  uint8_t extCrystal[] = {0x3F, 0x80};
  ret = i2cWriteData(i2c_ch, i2c_addr, &extCrystal, 2, 1000);
  if (!ret)
    return false;

  // 5.캘리브레이션 >> datasheet : p.81 >> 현재는 22바이트 연속 쓰기
  ret = i2cWriteData(i2c_ch, i2c_addr, &cal_data, 23, 1000);
  if (!ret)
    return false;

  // 6. 다시 CONFIG 모드 안정화 대기
  delay(1000);

  // 7. NDOF 모드로 전환: OPR_MODE = 0x0C
  uint8_t ndofMode[] = {0x3D, 0x0C};
  ret = i2cWriteData(i2c_ch, i2c_addr, &ndofMode, 2, 1000);
  if (!ret)
    return false;

  // 8. 모드 변경 후 내부 센서 안정화 대기
  delay(1000);

  // 9. 현재 모드 확인
  uint8_t startAddr = 0x3D;
  ret = i2cWriteData(i2c_ch, i2c_addr, &startAddr, 1, 1000);
  if (!ret)
    return false;

  ret = i2cReadData(i2c_ch, i2c_addr, &startAddr, 1, 1000);
  if (!ret)
    return false;

  logPrintf("[BNO_055] mode=%d\n", startAddr);

  return true;
}

bool bno055FindChip(void)
{
  bool ret = false;
  uint8_t data;
  ret = i2cReadData(i2c_ch, i2c_addr, &data, 1, 50);
  if(ret)
  {
    if(data == BNO055_CHIP_ID)
    {
      ret = false;
    }
  }
  return ret;
}

bool bno055ReadData(bno_055_data_t *data)
{
  bool ret = false;
  uint8_t startAddr = 0x1A;
  uint8_t sensorData[6] = {0};

  ret = i2cWriteData(i2c_ch, i2c_addr, &startAddr, 1, 50); // 읽기 시작 주소 지정
  if(ret == false)
  {
    // logPrintf("address write fail\n");
  }         

  uint8_t euler_raw[6];
  ret = i2cReadData(i2c_ch, i2c_addr, &euler_raw, 6, 50);
  if(ret == false)
  {
    // logPrintf("data read fail\n");
  }                           

  int16_t roll  = ((int16_t)euler_raw[1] << 8) | euler_raw[0];
  int16_t pitch = ((int16_t)euler_raw[3] << 8) | euler_raw[2];
  int16_t yaw   = ((int16_t)euler_raw[5] << 8) | euler_raw[4];

  float roll_deg  = roll  / 16.0f;
  float pitch_deg = pitch / 16.0f;
  float yaw_deg   = yaw   / 16.0f;

  logPrintf("[BNO055] roll=%5d, pitch=%5d, yaw=%5d\n", (int16_t)roll_deg, (int16_t)pitch_deg, (int16_t)yaw_deg);

  return ret;
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

      delay(100);
      cliGui()->moveUp(1);
    }
    cliGui()->moveDown(1);
    cliGui()->showCursor(true);

    ret = true;
  }
}
