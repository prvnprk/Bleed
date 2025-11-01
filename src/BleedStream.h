//
// Created by Praveen P on 01-11-2025.
//

#ifndef BLEED_BLEEDSTREAM_H
#define BLEED_BLEEDSTREAM_H

#include <sys/socket.h>

class BleedStream {

    int server_socket;

    public:
    BleedStream();
    ~BleedStream();
};


#endif //BLEED_BLEEDSTREAM_H