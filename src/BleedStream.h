//
// Created by Praveen P on 01-11-2025.
//

#ifndef BLEED_BLEEDSTREAM_H
#define BLEED_BLEEDSTREAM_H



#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <iostream>

#include "../include/lua/lua.hpp"

#include "BleedLua.h"

class BleedStream {

    int server_socket;
    sockaddr_in addr{};

    public:
    BleedStream();
    int serverSetup();
    int serverLoop();
    ~BleedStream();
};


#endif //BLEED_BLEEDSTREAM_H