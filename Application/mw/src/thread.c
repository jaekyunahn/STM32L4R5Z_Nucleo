
#include "ap_def.h"
#include "cmsis_os.h"

#ifdef _USE_HW_THREAD


#define lock()      xSemaphoreTake(mutex_lock, portMAX_DELAY);
#define unLock()    xSemaphoreGive(mutex_lock);


typedef struct thread_t_
{
  char          name[32];
  void          (*main)(void const *arg);
  void          *arg;
  bool          is_begin;
  osPriority    priority;
  uint32_t      stack_bytes;
  osThreadDef_t thread_def;
  osThreadId    thread_id;
} thread_t;

typedef struct
{
  int32_t count;
  thread_t thread[THREAD_MAX_CNT];
} thread_info_t;


static void cliThread(cli_args_t *args);

static bool is_begin = false;

static SemaphoreHandle_t mutex_lock;
static thread_info_t info;


bool threadInit(void)
{
  info.count = 0;

  mutex_lock = xSemaphoreCreateMutex();
  memset(&info, 0, sizeof(thread_info_t));

  logPrintf("[\033[32mOK\033[0m] threadInit()\n");

  cliAdd("thread", cliThread);
  return true;
}

bool threadCreate(const char *name, void (*func)(void const *arg), void *arg, osPriority priority, uint32_t stack_bytes)
{
  bool ret = false;
  uint32_t index;
  assert_param(info.count < THREAD_MAX_CNT);


  lock();
  if (info.count < THREAD_MAX_CNT)
  {    
    index = info.count;

    strcpy(info.thread[index].name, name);
    info.thread[index].main = func;
    info.thread[index].priority = priority;
    info.thread[index].stack_bytes = stack_bytes;

    info.count = index + 1;
    ret = true;
  }
  unLock();

  return ret;
}

bool threadBegin(void)
{
  bool ret = true;


  lock();
  logPrintf("[  ] threadBegin()\n");
  logPrintf("       count : %d\n", info.count);

  for (int i=0; i<info.count; i++)
  {
    if (info.thread[i].main != NULL && info.thread[i].is_begin == false)
    {
      info.thread[i].thread_def.name      = (char *)info.thread[i].name;
      info.thread[i].thread_def.pthread   = info.thread[i].main;
      info.thread[i].thread_def.instances = 0;
      info.thread[i].thread_def.stacksize = info.thread[i].stack_bytes/4;
      info.thread[i].thread_def.tpriority = info.thread[i].priority;
      info.thread[i].thread_id = osThreadCreate(&info.thread[i].thread_def, info.thread[i].arg);
      assert_param(info.thread[i].thread_id);

      if (info.thread[i].thread_id != NULL)
      {
        info.thread[i].is_begin = true;
        logPrintf("       OK   - %s\n", info.thread[i].name);
      }
      else
      {
        logPrintf("       Fail - %s Fail\n", info.thread[i].name);
      }
    }
  }

  logPrintf("       Free Heap : %d bytes / %d bytes\n", xPortGetFreeHeapSize(), configTOTAL_HEAP_SIZE);
  unLock();

  is_begin = true;

  return ret;
}


void cliThread(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    thread_t *p_thread;
    TaskStatus_t task_status;

    cliPrintf("cpu usage : %d %%\n", osGetCPUUsage());
    cliPrintf("is_begin  : %s\n", is_begin ? "True":"False");
    cliPrintf("count     : %d\n", info.count);
    p_thread = info.thread;
    for (int i=0; i<info.count; i++)
    {
      vTaskGetInfo(p_thread[i].thread_id, &task_status, pdTRUE, eInvalid);

      cliPrintf("%-16s, stack : %4d free %04d, prio : %d\n",
                p_thread[i].name,
                p_thread[i].stack_bytes,
                (int)task_status.usStackHighWaterMark * 4,
                p_thread[i].priority
                );
    }
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "task"))
  {
    const size_t bytes_per_task = 40;
    char *list_buf;

    list_buf = (char *)pvPortMalloc(uxTaskGetNumberOfTasks() * bytes_per_task);

    vTaskList(list_buf);
    cliPrintf("Task Name\tState\tPrio\tStack\tNum#\n");
    cliWrite((uint8_t *)list_buf, strlen(list_buf));
    vPortFree(list_buf);

    cliPrintf("Free Heap : %d bytes\n", xPortGetFreeHeapSize());
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("thread info\n");
    cliPrintf("thread task\n");
  }
}


#endif
