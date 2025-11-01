//
// Created by Praveen P on 01-11-2025.
//

#include "BleedStream.h"

BleedStream::BleedStream() {
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
}

BleedStream::~BleedStream() {

}

