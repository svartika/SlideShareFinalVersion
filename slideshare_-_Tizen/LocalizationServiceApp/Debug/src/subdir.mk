################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataParser.cpp \
../src/LocalizationServiceAppApp.cpp \
../src/LocalizationServiceAppEntry.cpp \
../src/LocationManagerThread.cpp \
../src/MessagePort.cpp \
../src/NotificationManagerThread.cpp \
../src/Storage.cpp 

OBJS += \
./src/DataParser.o \
./src/LocalizationServiceAppApp.o \
./src/LocalizationServiceAppEntry.o \
./src/LocationManagerThread.o \
./src/MessagePort.o \
./src/NotificationManagerThread.o \
./src/Storage.o 

CPP_DEPS += \
./src/DataParser.d \
./src/LocalizationServiceAppApp.d \
./src/LocalizationServiceAppEntry.d \
./src/LocationManagerThread.d \
./src/MessagePort.d \
./src/NotificationManagerThread.d \
./src/Storage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	clang++.exe -I"pch" -D_DEBUG -I"C:\Users\AJOU\Desktop\slideshare-master (1)\slideshare-master\LocalizationServiceApp\inc" -O0 -g3 -Wall -c -fmessage-length=0 -target arm-tizen-linux-gnueabi -gcc-toolchain "C:/tizen-sdk/tools/smart-build-interface/../arm-linux-gnueabi-gcc-4.5/" -ccc-gcc-name arm-linux-gnueabi-g++ -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mtune=cortex-a8 -Wno-gnu -fPIE --sysroot="C:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-device-2.2.native" -I"C:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-device-2.2.native/usr/include/libxml2" -I"C:\tizen-sdk\library" -I"C:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-device-2.2.native/usr/include" -I"C:/tizen-sdk/platforms/tizen2.2/rootstraps/tizen-device-2.2.native/usr/include/osp" -D_APP_LOG -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


