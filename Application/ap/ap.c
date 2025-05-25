#include "ap.h"

void apInit(void)
{
  systemInit();
}

void apMain(void)
{
  systemMain();
  assert_param(0);
}
