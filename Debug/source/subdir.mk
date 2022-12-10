################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DigitalAngleGauge.c \
../source/accel.c \
../source/cbfifo.c \
../source/cmd.c \
../source/i2c.c \
../source/led.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/systick.c \
../source/test_accel.c \
../source/test_cbfifo.c \
../source/test_led.c \
../source/uart.c 

C_DEPS += \
./source/DigitalAngleGauge.d \
./source/accel.d \
./source/cbfifo.d \
./source/cmd.d \
./source/i2c.d \
./source/led.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/systick.d \
./source/test_accel.d \
./source/test_cbfifo.d \
./source/test_led.d \
./source/uart.d 

OBJS += \
./source/DigitalAngleGauge.o \
./source/accel.o \
./source/cbfifo.o \
./source/cmd.o \
./source/i2c.o \
./source/led.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/systick.o \
./source/test_accel.o \
./source/test_cbfifo.o \
./source/test_led.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\board" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\source" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\drivers" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\CMSIS" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\utilities" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\DigitalAngleGauge\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/DigitalAngleGauge.d ./source/DigitalAngleGauge.o ./source/accel.d ./source/accel.o ./source/cbfifo.d ./source/cbfifo.o ./source/cmd.d ./source/cmd.o ./source/i2c.d ./source/i2c.o ./source/led.d ./source/led.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/systick.d ./source/systick.o ./source/test_accel.d ./source/test_accel.o ./source/test_cbfifo.d ./source/test_cbfifo.o ./source/test_led.d ./source/test_led.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

