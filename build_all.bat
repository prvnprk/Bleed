@echo off


set NDK_PATH=D:/toolchains/android-ndk-r27d-windows/android-ndk-r27d


echo [Building arm64-v8a]
mkdir build64
cd build64
cmake .. -G Ninja ^
    -DCMAKE_SYSTEM_NAME=Android ^
    -DCMAKE_SYSTEM_VERSION=21 ^
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a ^
    -DCMAKE_ANDROID_NDK=%NDK_PATH% ^
    -DCMAKE_ANDROID_STL_TYPE=c++_static

cmake --build .
cd ..
echo.


echo [Building armeabi-v7a]
mkdir build32
cd build32
cmake .. -G Ninja ^
    -DCMAKE_SYSTEM_NAME=Android ^
    -DCMAKE_SYSTEM_VERSION=21 ^
    -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a ^
    -DCMAKE_ANDROID_NDK=%NDK_PATH% ^
    -DCMAKE_ANDROID_STL_TYPE=c++_static

cmake --build .
cd ..

echo [Done]
pause