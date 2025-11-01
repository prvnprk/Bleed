//
// Created by Praveen P on 01-11-2025.
//

#include "redirectOutput.h"

// https://codelab.wordpress.com/2014/11/03/how-to-use-standard-output-streams-for-logging-in-android-apps/

static void *thread_func(void*);


static int pfd[2];
static pthread_t thr;
static const char *tag = "myapp";

int start_logger(const char *app_name)
{
    tag = app_name;

    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

    pipe(pfd);
    dup2(pfd[1], 1);
    dup2(pfd[1], 2);


    if(pthread_create(&thr, 0, thread_func, 0) == -1)
        return -1;
    pthread_detach(thr);
    return 0;
}

static void *thread_func(void*)
{
    ssize_t rdsz;
    char buf[128];
    while((rdsz = read(pfd[0], buf, sizeof buf - 1)) > 0) {
        if(buf[rdsz - 1] == '\n') --rdsz;
        buf[rdsz] = 0;  /* add null-terminator */
        __android_log_write(ANDROID_LOG_DEBUG, tag, buf);
    }
    return 0;
}