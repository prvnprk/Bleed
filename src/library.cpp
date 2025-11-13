#include "library.h"
#include <fstream>

static std::thread helloThread;

std::ifstream mem_maps;

void hello() {
    BleedLua *lua = new BleedLua();
    lua->execString(R"(
            print("lua Test")

        )");
    delete lua;

    sleep(10);

    std::cout << "test in new thread" << std::endl;

    std::stringstream mapsstream;
    mapsstream << mem_maps.rdbuf();

    std::cout << mapsstream.str() << std::endl;




    BleedStream *stream = new BleedStream();
    printf("hello world stdout1\n");
    if (stream->serverSetup() == 1) {
        printf("server error\n");
    }
    stream->serverLoop();
    delete stream;


    while (true) {
        printf("hello world stdout\n");
        sleep(1);
    }

    mem_maps.close();

}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    start_logger("BLEED: ");

    mem_maps = std::ifstream("/proc/self/maps");



    if (mem_maps.is_open()) {
        printf("Successfully accessed /proc/self/");
    } else {
        printf("Failed to access /proc/self/");
    }

    pid_t current_pid = getpid();
    printf("The PID of the current process is: %d\n", current_pid);

    helloThread = std::thread(&hello);

    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    if (helloThread.joinable()) helloThread.join();
}