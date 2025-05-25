#ifndef AP_DEF_H_
#define AP_DEF_H_

#include "hw.h"
#include "ap.h"
#include "mw.h"

typedef struct 
{
  void (*begin)(void);
  void (*run)(void);
  void (*end)(void);
} state_func_t;


#endif
