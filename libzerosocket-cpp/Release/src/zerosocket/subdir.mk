################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/zerosocket/Config.cpp \
../src/zerosocket/Egress.cpp \
../src/zerosocket/FileConfig.cpp \
../src/zerosocket/Ingress.cpp 

OBJS += \
./src/zerosocket/Config.o \
./src/zerosocket/Egress.o \
./src/zerosocket/FileConfig.o \
./src/zerosocket/Ingress.o 

CPP_DEPS += \
./src/zerosocket/Config.d \
./src/zerosocket/Egress.d \
./src/zerosocket/FileConfig.d \
./src/zerosocket/Ingress.d 


# Each subdirectory must supply rules for building sources it contributes
src/zerosocket/%.o: ../src/zerosocket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I. -I.. -I../src/jsmn -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


