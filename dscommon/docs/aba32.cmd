@echo off

rem Common ANDROID options
set ANDROID_HOME=D:/msys64/qt/Tools/android-sdk
set ANDROID_SDK_ROOT=%ANDROID_HOME%
set ANDROID_NDK_ROOT=D:/msys64/qt/Tools/android-ndk-r16b
set ANDROID_NDK_HOST=windows-x86_64
set ANDROID_NDK_TOOLCHAIN_VERSION=4.9

rem for 32bits may be after API Version 18
set ANDROID_NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
set ANDROID_NDK_TOOLS_PREFIX=arm-linux-androideabi
set ANDROID_NDK_PLATFORM=android-18
set ANDROID_API_VERSION=android-18

set JAVA_HOME=C:/Program Files/Java/jdk1.8.0_161
set PATH=%PATH%;%ANDROID_HOME%\tools;%JAVA_HOME%\bin;%ANDROID_NDK_ROOT%\prebuilt\%ANDROID_NDK_HOST%\bin

rem Qt paths for differents platforms
set PATH=%PATH%;D:\msys64\qt\5.12.0\android_armv7\bin
