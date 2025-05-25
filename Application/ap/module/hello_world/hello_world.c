#include "module.h"

#define lock()   xSemaphoreTake(mutex_lock, portMAX_DELAY);
#define unLock() xSemaphoreGive(mutex_lock);

static bool helloworldInit(void);
static void helloworldThread(void const *arg);

static void cliHelloworld(cli_args_t *args);

MODULE_DEF(cli)
{
  .name = "hello_world",
  .priority = MODULE_PRI_NORMAL,
  .init = helloworldInit
};
static SemaphoreHandle_t mutex_lock;
static bool is_init = false;

bool helloworldInit(void)
{
  mutex_lock = xSemaphoreCreateMutex();
  is_init = threadCreate("hello_world", helloworldThread, NULL, _HW_DEF_THREAD_PRI, _HW_DEF_THREAD_STACK);
  assert(mutex_lock);
  assert(is_init);

  cliAdd("hello_world", cliHelloworld);

  logPrintf("[%s] helloworldInit()\n", is_init ? "\033[32mOK\033[0m":"\033[31mNG\033[0m");
  return is_init;
}

void helloworldThread(void const *arg)
{
	UNUSED(arg);

  bool init_ret = true;

  systemWaitStart();

  logPrintf("[%s] Thread Started : HELLO_WORLD\n", init_ret ? "\033[32mOK\033[0m":"\033[31mNG\033[0m" );
  while(1)
  {
  	//cliPrintf("[app]hello world!\n");
  	//debug_memory();
    delay(5);
  }
}

static void cliHelloworld(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 0)
  {
  	cliPrintf("hello world!\n");
    ret = true;
  }

  if (ret == false)
  {

  }
}
