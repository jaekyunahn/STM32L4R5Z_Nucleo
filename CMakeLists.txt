cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(arm-none-eabi-gcc)

set(PRJ_NAME stm32l4r5z-nucleofw)


project(${PRJ_NAME}
  LANGUAGES ASM C CXX
)


set(EXECUTABLE ${PRJ_NAME}.elf)


file(GLOB SRC_FILES CONFIGURE_DEPENDS

  Core/src/*c
  Application/ap/*.c
  Application/bsp/*.c
  Application/common/*.c
  Application/hw/*.c
  Application/mw/*.c
  Application/lib/*.c

  Application/lib/FatFs/src/*.c
  Application/lib/FatFs/src/option/syscall.c
  Application/lib/FatFs/src/option/unicode.c

  FATFS/App/*.c
  FATFS/Target/*.c

#  src/*.c
#  src/bsp/*.c
#  src/bsp/device/*.c
#  src/bsp/rtos/*.c
#
  Middlewares/Third_Party/FreeRTOS/Source/*c
  Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c
  Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/*.c    
  Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
#  src/lib/FreeRTOS/Source/*.c
#  src/lib/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c
#  src/lib/FreeRTOS/Source/CMSIS_RTOS/*.c    
#  src/lib/FreeRTOS/Source/portable/MemMang/heap_4.c
)

file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  Application/ap/*.c
  Application/bsp/*.c
  Application/common/*.c
  Application/hw/*.c
  Application/mw/*.c

  Core/Startup/*s

  Drivers/STM32L4xx_HAL_Driver/Src/*c

#  src/ap/*.c
#  src/bsp/*.s
#  src/common/*.c
#  src/hw/*.c
#  src/lib/STM32L4xx_HAL_Driver/Src/*.c
#  src/lib/STM32_USB_Device_Library/Core/Src/*.c
#  src/lib/littlefs/*.c
)

add_executable(${EXECUTABLE} 
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)


# include file
target_include_directories(${EXECUTABLE} PRIVATE 
  Core/Inc
  Drivers/STM32L4xx_HAL_Driver/Inc
  Drivers/STM32L4xx_HAL_Driver/Inc/Legacy
  Middlewares/Third_Party/FreeRTOS/Source/include
  Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
  Drivers/CMSIS/Device/ST/STM32L4xx/Include
  Drivers/CMSIS/Include
  Application/ap 
  Application/bsp 
  Application/common 
  Application/hw 
  Application/ap/module 
  Application/ap/module/system 
  Application/common/core 
  Application/hw/deviceDriver/inc 
  Application/hw/moduleDriver/inc 
  Application/mw 
  Application/mw/inc 
  Application/lib 
  Application/lib/FatFs/src
  Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
)

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DUSE_HAL_DRIVER
  -DUSE_FULL_ASSERT
  -DSTM32L4R5xx
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections
  -fstack-usage  
  -Wmissing-field-initializers
  -Wuninitialized 
  -Wenum-conversion

  -Wall
  -g3
  -O0
  )

target_link_options(${EXECUTABLE} PRIVATE
  -T../STM32L4R5ZITXP_FLASH.ld
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nano.specs
  -lc
  -lm
  -lstdc++
  -lsupc++
  # -lnosys
  -Wl,-Map=${PRJ_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
  )

add_custom_command(TARGET ${EXECUTABLE} 
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
  COMMENT "Invoking: Make Binary"
  )  