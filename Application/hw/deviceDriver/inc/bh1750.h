#ifndef BH1750_H_
#define BH1750_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "hw.h"

// typedef struct
// {
//   void (*init)(void);
//   void (*init)(void);
// } bh1750_driver_t;

void bh1750Init(void);
bool bh1750IsInit(void);
bool bh1750StartUp(void);
bool bh1750FindChip(void);
bool bh1750ReadLux(float *lux);

#ifdef __cplusplus
}
#endif

#endif