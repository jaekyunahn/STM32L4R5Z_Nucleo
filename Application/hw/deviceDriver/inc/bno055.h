#ifndef BNO055_H_
#define BNO055_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "hw.h"

#define BNO055_I2C_ADDRESS  0x29
#define BNO055_CHIP_ID      0x40

typedef struct
{
  // 가속도 (g 단위)
  float ax_g;
  float ay_g;
  float az_g;
  // 자기장 (µT)
  float mx_uT;
  // 자이로 (deg/s)
  float gx_dps;
  float gy_dps;
  float gz_dps;
} bno_055_data_t;

void bno055Init(void);
bool bno055IsInit(void);
bool bno055StartUp(void);
bool bno055FindChip(void);
bool bno055ReadData(bno_055_data_t *data);

#ifdef __cplusplus
}
#endif

#endif