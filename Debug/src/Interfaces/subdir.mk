################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Interfaces/IGetCollisionData.cpp \
../src/Interfaces/IGetRenderData.cpp \
../src/Interfaces/IUpdateable.cpp 

OBJS += \
./src/Interfaces/IGetCollisionData.o \
./src/Interfaces/IGetRenderData.o \
./src/Interfaces/IUpdateable.o 

CPP_DEPS += \
./src/Interfaces/IGetCollisionData.d \
./src/Interfaces/IGetRenderData.d \
./src/Interfaces/IUpdateable.d 


# Each subdirectory must supply rules for building sources it contributes
src/Interfaces/%.o: ../src/Interfaces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


