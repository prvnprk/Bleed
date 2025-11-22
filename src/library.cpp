#include "library.h"
#include <fstream>

static std::thread helloThread;


void hello() {


    sleep(10);

    std::cout << "test in new thread" << std::endl;



    BleedStream *stream = new BleedStream();
    printf("hello world stdout1\n");
    if (stream->serverSetup() == 1) {
        printf("server error\n");
    }
    stream->serverLoop();
    delete stream;

}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    start_logger("BLEED: ");

    currentBleedState.mem_maps = std::ifstream("/proc/self/maps");

    currentBleedState.mem = open("/proc/self/mem", O_RDONLY);

    if (currentBleedState.mem == -1) {
        // printf("Error opening /proc/self/mem\n");
        char *errorMessage = strerror(errno);
        printf("Error opening /proc/self/mem: %s\n", errorMessage);

    }



    if (currentBleedState.mem_maps.is_open()) {
        printf("Successfully accessed /proc/self/maps");
    } else {
        printf("Failed to access /proc/self/maps");
    }

    pid_t current_pid = getpid();
    printf("The PID of the current process is: %d\n", current_pid);

    helloThread = std::thread(&hello);

    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
   close( currentBleedState.mem);
    currentBleedState.mem_maps.close();
    if (helloThread.joinable()) helloThread.join();
}