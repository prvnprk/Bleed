cmake_minimum_required(VERSION 3.21)


set(CMAKE_ANDROID_NDK "D:/toolchains/android-ndk-r27d-windows/android-ndk-r27d")


set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 21)
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
set(CMAKE_ANDROID_STL_TYPE c++_static)


set(CMAKE_C_COMPILER "${CMAKE_ANDROID_NDK}/toolchains/llvm/prebuilt/windows-x86_64/bin/clang.exe")
set(CMAKE_CXX_COMPILER "${CMAKE_ANDROID_NDK}/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe")

set(CMAKE_GENERATOR Ninja)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Bleed)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -llog ")


add_library(Bleed SHARED src/library.cpp
        src/BleedLua.cpp
        src/BleedLua.h
        src/bridge.h
        src/redirectOutput.cpp
        src/redirectOutput.h
        src/BleedStream.cpp
        src/BleedStream.h
)
target_include_directories(Bleed PRIVATE ${CMAKE_SOURCE_DIR}/include)





target_link_libraries(Bleed
        ${CMAKE_SOURCE_DIR}/lib/liblua.a
)