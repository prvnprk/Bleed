##cmake .. -G Ninja -DCMAKE_SYSTEM_NAME=Android -DCMAKE_SYSTEM_VERSION=21 -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a -DCMAKE_ANDROID_NDK=D:/toolchains/android-ndk-r27d-windows/android-ndk-r27d -DCMAKE_ANDROID_STL_TYPE=c++_static

cmake_minimum_required(VERSION 3.21)

project(Bleed)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")

add_library(Bleed SHARED
        src/library.cpp
        src/BleedLua.cpp
        src/BleedLua.h
        src/bridge.h
        src/redirectOutput.cpp
        src/redirectOutput.h
        src/BleedStream.cpp
        src/BleedStream.h
        src/states.cpp
        src/states.h
)

target_include_directories(Bleed PRIVATE ${CMAKE_SOURCE_DIR}/include)


if(${CMAKE_ANDROID_ARCH_ABI} STREQUAL "arm64-v8a")

    message(STATUS "Building for arm64-v8a, linking liblua64.a")
    set(LUA_LIB "${CMAKE_SOURCE_DIR}/lib/liblua64.a")
elseif(${CMAKE_ANDROID_ARCH_ABI} STREQUAL "armeabi-v7a")

    message(STATUS "Building for armeabi-v7a, linking liblua32.a")
    set(LUA_LIB "${CMAKE_SOURCE_DIR}/lib/liblua32.a")
else()
    message(FATAL_ERROR "Unsupported Architecture: ${CMAKE_ANDROID_ARCH_ABI}")
endif()

target_link_libraries(Bleed
        ${LUA_LIB}
        log
)
