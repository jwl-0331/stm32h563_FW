################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.c \
../Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.c 

OBJS += \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.o \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.o 

C_DEPS += \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.d \
./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/MQTT/MQTTPacket/%.o Middlewares/Third_Party/MQTT/MQTTPacket/%.su Middlewares/Third_Party/MQTT/MQTTPacket/%.cyclo: ../Middlewares/Third_Party/MQTT/MQTTPacket/%.c Middlewares/Third_Party/MQTT/MQTTPacket/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Core/App/aws" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/MQTT/MQTTPacket" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-MQTT-2f-MQTTPacket

clean-Middlewares-2f-Third_Party-2f-MQTT-2f-MQTTPacket:
	-$(RM) ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectClient.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTConnectServer.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTDeserializePublish.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTFormat.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTPacket.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSerializePublish.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeClient.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTSubscribeServer.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeClient.su ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.cyclo ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.d ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.o ./Middlewares/Third_Party/MQTT/MQTTPacket/MQTTUnsubscribeServer.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-MQTT-2f-MQTTPacket

