################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/LWIP/Target/ethernetif.c 

OBJS += \
./Drivers/BSP/LWIP/Target/ethernetif.o 

C_DEPS += \
./Drivers/BSP/LWIP/Target/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/LWIP/Target/%.o Drivers/BSP/LWIP/Target/%.su Drivers/BSP/LWIP/Target/%.cyclo: ../Drivers/BSP/LWIP/Target/%.c Drivers/BSP/LWIP/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT/MQTTPacket" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/mbedtls" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Core/App/aws" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-LWIP-2f-Target

clean-Drivers-2f-BSP-2f-LWIP-2f-Target:
	-$(RM) ./Drivers/BSP/LWIP/Target/ethernetif.cyclo ./Drivers/BSP/LWIP/Target/ethernetif.d ./Drivers/BSP/LWIP/Target/ethernetif.o ./Drivers/BSP/LWIP/Target/ethernetif.su

.PHONY: clean-Drivers-2f-BSP-2f-LWIP-2f-Target

