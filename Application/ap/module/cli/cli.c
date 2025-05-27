#include "module.h"

static bool cliModuleInit(void);
static void cliThread(void const *arg);

MODULE_DEF(cli) 
{
  .name = "cli",
  .priority = MODULE_PRI_NORMAL,
  .init = cliModuleInit
};





bool cliModuleInit(void)
{
  bool ret;

  cliOpen(_DEF_UART1, 115200);

  ret = threadCreate("cli", cliThread, NULL, _HW_DEF_THREAD_PRI, _HW_DEF_THREAD_STACK * 2);
  assert_param(ret);

  logPrintf("[%s] cliModuleInit()\n", ret ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");
  return ret;
}

void cliThread(void const *arg)
{
	UNUSED(arg);

  bool init_ret = true;

  systemWaitStart();

  logPrintf("[%s] Thread Started : CLI\n", init_ret ? "\033[32mOK\033[0m":"\033[31mNG\033[0m" );
  while(1)
  {
    cliMain();
    delay(5);
  }
}

