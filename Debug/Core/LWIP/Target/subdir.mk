################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LWIP/Target/ethernetif.c 

OBJS += \
./Core/LWIP/Target/ethernetif.o 

C_DEPS += \
./Core/LWIP/Target/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LWIP/Target/%.o Core/LWIP/Target/%.su Core/LWIP/Target/%.cyclo: ../Core/LWIP/Target/%.c Core/LWIP/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Core/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I"C:/CubeWorspace/stm32h563_fw/Core/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Core/LWIP/Target" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LWIP-2f-Target

clean-Core-2f-LWIP-2f-Target:
	-$(RM) ./Core/LWIP/Target/ethernetif.cyclo ./Core/LWIP/Target/ethernetif.d ./Core/LWIP/Target/ethernetif.o ./Core/LWIP/Target/ethernetif.su

.PHONY: clean-Core-2f-LWIP-2f-Target

