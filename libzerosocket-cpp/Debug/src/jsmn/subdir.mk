################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/jsmn/jsmn.c 

OBJS += \
./src/jsmn/jsmn.o 

C_DEPS += \
./src/jsmn/jsmn.d 


# Each subdirectory must supply rules for building sources it contributes
src/jsmn/%.o: ../src/jsmn/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I. -I.. -I../src/jsmn -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


