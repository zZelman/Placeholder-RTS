################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Rooms/CRoom.cpp \
../src/Rooms/CRoom_Container.cpp \
../src/Rooms/CRoom_kitchen.cpp \
../src/Rooms/CRoom_powerPlant.cpp \
../src/Rooms/CRoom_researchSpawner.cpp \
../src/Rooms/CRoom_smithy.cpp \
../src/Rooms/CRoom_supportSpawner.cpp \
../src/Rooms/CRoom_warSpawner.cpp \
../src/Rooms/CRoom_warehouse.cpp 

OBJS += \
./src/Rooms/CRoom.o \
./src/Rooms/CRoom_Container.o \
./src/Rooms/CRoom_kitchen.o \
./src/Rooms/CRoom_powerPlant.o \
./src/Rooms/CRoom_researchSpawner.o \
./src/Rooms/CRoom_smithy.o \
./src/Rooms/CRoom_supportSpawner.o \
./src/Rooms/CRoom_warSpawner.o \
./src/Rooms/CRoom_warehouse.o 

CPP_DEPS += \
./src/Rooms/CRoom.d \
./src/Rooms/CRoom_Container.d \
./src/Rooms/CRoom_kitchen.d \
./src/Rooms/CRoom_powerPlant.d \
./src/Rooms/CRoom_researchSpawner.d \
./src/Rooms/CRoom_smithy.d \
./src/Rooms/CRoom_supportSpawner.d \
./src/Rooms/CRoom_warSpawner.d \
./src/Rooms/CRoom_warehouse.d 


# Each subdirectory must supply rules for building sources it contributes
src/Rooms/%.o: ../src/Rooms/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


