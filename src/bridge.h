//
// Created by Praveen P on 26-10-2025.
//

#ifndef BLEED_BRIDGE_H
#define BLEED_BRIDGE_H
#include <jni.h>
/* Header for class mainProgram */

#ifndef _Included_mainProgram
#define _Included_mainProgram
#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Class:     mainProgram
     * Method:    luatestv
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_mainProgram_luatestv
      (JNIEnv *, jobject);
    JNIEXPORT void JNICALL Java_com_vectorunit_purple_googleplay_Purple_luatestp(JNIEnv *env, jobject thiz);
    jint JNI_OnLoad(JavaVM *vm, void *reserved);

#ifdef __cplusplus
}
#endif
#endif

#endif //BLEED_BRIDGE_H