################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ARender.cpp \
../src/AUpdate.cpp \
../src/AUserInput.cpp \
../src/CGame.cpp \
../src/CRoom.cpp \
../src/CRoom_Container.cpp \
../src/CSprite.cpp \
../src/CTexture.cpp \
../src/CTile.cpp \
../src/CTile_Container.cpp \
../src/CUnit.cpp \
../src/CUnit_Container.cpp \
../src/DPhysics.cpp \
../src/IRenderable.cpp \
../src/IUpdateable.cpp \
../src/Utills.cpp \
../src/main.cpp 

OBJS += \
./src/ARender.o \
./src/AUpdate.o \
./src/AUserInput.o \
./src/CGame.o \
./src/CRoom.o \
./src/CRoom_Container.o \
./src/CSprite.o \
./src/CTexture.o \
./src/CTile.o \
./src/CTile_Container.o \
./src/CUnit.o \
./src/CUnit_Container.o \
./src/DPhysics.o \
./src/IRenderable.o \
./src/IUpdateable.o \
./src/Utills.o \
./src/main.o 

CPP_DEPS += \
./src/ARender.d \
./src/AUpdate.d \
./src/AUserInput.d \
./src/CGame.d \
./src/CRoom.d \
./src/CRoom_Container.d \
./src/CSprite.d \
./src/CTexture.d \
./src/CTile.d \
./src/CTile_Container.d \
./src/CUnit.d \
./src/CUnit_Container.d \
./src/DPhysics.d \
./src/IRenderable.d \
./src/IUpdateable.d \
./src/Utills.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


