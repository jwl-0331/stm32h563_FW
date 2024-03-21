################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app_freertos.c \
../Core/Src/main.c \
../Core/Src/stm32h5xx_hal_msp.c \
../Core/Src/stm32h5xx_hal_timebase_tim.c \
../Core/Src/stm32h5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h5xx.c 

OBJS += \
./Core/Src/app_freertos.o \
./Core/Src/main.o \
./Core/Src/stm32h5xx_hal_msp.o \
./Core/Src/stm32h5xx_hal_timebase_tim.o \
./Core/Src/stm32h5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h5xx.o 

C_DEPS += \
./Core/Src/app_freertos.d \
./Core/Src/main.d \
./Core/Src/stm32h5xx_hal_msp.d \
./Core/Src/stm32h5xx_hal_timebase_tim.d \
./Core/Src/stm32h5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h5xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT/MQTTPacket" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Core/App/aws" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32h5xx_hal_msp.cyclo ./Core/Src/stm32h5xx_hal_msp.d ./Core/Src/stm32h5xx_hal_msp.o ./Core/Src/stm32h5xx_hal_msp.su ./Core/Src/stm32h5xx_hal_timebase_tim.cyclo ./Core/Src/stm32h5xx_hal_timebase_tim.d ./Core/Src/stm32h5xx_hal_timebase_tim.o ./Core/Src/stm32h5xx_hal_timebase_tim.su ./Core/Src/stm32h5xx_it.cyclo ./Core/Src/stm32h5xx_it.d ./Core/Src/stm32h5xx_it.o ./Core/Src/stm32h5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h5xx.cyclo ./Core/Src/system_stm32h5xx.d ./Core/Src/system_stm32h5xx.o ./Core/Src/system_stm32h5xx.su

.PHONY: clean-Core-2f-Src

