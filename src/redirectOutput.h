//
// Created by Praveen P on 01-11-2025.
//

#ifndef BLEED_REDIRECTOUTPUT_H
#define BLEED_REDIRECTOUTPUT_H

#include <android/log.h>
#include <thread>
#include <unistd.h>

int start_logger(const char *app_name);
static void *thread_func(void*);

#endif //BLEED_REDIRECTOUTPUT_H