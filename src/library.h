#ifndef BLEED_LIBRARY_H
#define BLEED_LIBRARY_H

#include <jni.h>
#include <iostream>
#include "BleedLua.h"
#include <android/log.h>
#include <thread>
#include "redirectOutput.h"
#include "BleedStream.h"
jint JNI_OnLoad(JavaVM *vm, void *reserved);
void hello();

#endif // BLEED_LIBRARY_H