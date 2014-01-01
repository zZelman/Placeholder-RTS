################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Physics/CPhysicsEngine.cpp \
../src/Physics/CQuadTree.cpp \
../src/Physics/DPhysics.cpp 

OBJS += \
./src/Physics/CPhysicsEngine.o \
./src/Physics/CQuadTree.o \
./src/Physics/DPhysics.o 

CPP_DEPS += \
./src/Physics/CPhysicsEngine.d \
./src/Physics/CQuadTree.d \
./src/Physics/DPhysics.d 


# Each subdirectory must supply rules for building sources it contributes
src/Physics/%.o: ../src/Physics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


