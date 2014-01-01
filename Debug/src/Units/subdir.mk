################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Units/CUnit.cpp \
../src/Units/CUnit_Container.cpp 

OBJS += \
./src/Units/CUnit.o \
./src/Units/CUnit_Container.o 

CPP_DEPS += \
./src/Units/CUnit.d \
./src/Units/CUnit_Container.d 


# Each subdirectory must supply rules for building sources it contributes
src/Units/%.o: ../src/Units/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


