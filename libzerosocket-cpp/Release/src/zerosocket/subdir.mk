################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/zerosocket/Config.cpp \
../src/zerosocket/Connection.cpp \
../src/zerosocket/ConnectionStore.cpp \
../src/zerosocket/Descriptor.cpp \
../src/zerosocket/Egress.cpp \
../src/zerosocket/FileConfig.cpp \
../src/zerosocket/Ingress.cpp \
../src/zerosocket/TCPConnection.cpp \
../src/zerosocket/UDPConnection.cpp \
../src/zerosocket/zerosocket.cpp 

OBJS += \
./src/zerosocket/Config.o \
./src/zerosocket/Connection.o \
./src/zerosocket/ConnectionStore.o \
./src/zerosocket/Descriptor.o \
./src/zerosocket/Egress.o \
./src/zerosocket/FileConfig.o \
./src/zerosocket/Ingress.o \
./src/zerosocket/TCPConnection.o \
./src/zerosocket/UDPConnection.o \
./src/zerosocket/zerosocket.o 

CPP_DEPS += \
./src/zerosocket/Config.d \
./src/zerosocket/Connection.d \
./src/zerosocket/ConnectionStore.d \
./src/zerosocket/Descriptor.d \
./src/zerosocket/Egress.d \
./src/zerosocket/FileConfig.d \
./src/zerosocket/Ingress.d \
./src/zerosocket/TCPConnection.d \
./src/zerosocket/UDPConnection.d \
./src/zerosocket/zerosocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/zerosocket/%.o: ../src/zerosocket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DMAXCONNECTION_SZ=20 -I. -I.. -I../src/jsmn -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


