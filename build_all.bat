@echo off
set NDK_PATH=D:/toolchains/android-ndk-r27d-windows/android-ndk-r27d


if not exist build mkdir build
cd build


echo [Building arm64-v8a]
if not exist arm64-v8a mkdir arm64-v8a
cd arm64-v8a


cmake ../.. -G Ninja ^
    -DCMAKE_SYSTEM_NAME=Android ^
    -DCMAKE_SYSTEM_VERSION=21 ^
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a ^
    -DCMAKE_ANDROID_NDK=%NDK_PATH% ^
    -DCMAKE_ANDROID_STL_TYPE=c++_static

cmake --build .

cd ..



echo.
echo [Building armeabi-v7a]
if not exist armeabi-v7a mkdir armeabi-v7a
cd armeabi-v7a

cmake ../.. -G Ninja ^
    -DCMAKE_SYSTEM_NAME=Android ^
    -DCMAKE_SYSTEM_VERSION=21 ^
    -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a ^
    -DCMAKE_ANDROID_NDK=%NDK_PATH% ^
    -DCMAKE_ANDROID_STL_TYPE=c++_static

cmake --build .

cd ..

echo [Done]
pause