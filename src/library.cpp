#include "library.h"



void hello() {
    BleedLua *lua = new BleedLua();
    lua->execString(R"(
            print("lua Test")
        )");
    delete lua;

    while (true) {
        printf("hello world stdout\n");
        sleep(1);
    }

}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    start_logger("BLEED: ");

    std::thread helloThread(&hello);
    helloThread.detach();
    return JNI_VERSION_1_4;
}