//
// Created by Praveen P on 01-11-2025.
//

#include "BleedStream.h"

#include "states.h"


BleedStream::BleedStream() {

    lua = new BleedLua();
    server_socket = socket(AF_INET, SOCK_STREAM, 0);


}

int BleedStream::serverSetup() {



    addr.sin_family = AF_INET;
    addr.sin_port = htons(1628);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (server_socket == -1) { perror("socket"); return 1; }
    if (bind(server_socket, (sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind"); return 1;
    }
    if (listen(server_socket, 5) == -1) { perror("listen"); return 1; }

    return 0;

}

int BleedStream::serverLoop() {

    // std::cout << "BleedStream::serverLoop" << std::endl;


    printf("serverloop\n");


    while (true) {
        sockaddr_in client{};
        socklen_t client_size = sizeof(client);
        currentBleedState.client_fd = accept(server_socket, (sockaddr*)&client, &client_size);


        if (currentBleedState.client_fd == -1) { perror("accept"); continue; }


        std::vector<char> buffer;
        buffer.reserve(4096);

        char temp[4096];
        ssize_t bytes = recv(currentBleedState.client_fd, temp, sizeof(temp), 0);
        if (bytes <= 0) { close(currentBleedState.client_fd); continue; }

        buffer.insert(buffer.end(), temp, temp + bytes);
        buffer.push_back('\0');

        std::cout << "Executing: " << buffer.data() << "\n";

        if (lua->execString(buffer.data()) != LUA_OK) {
            const char* err = lua->luaToString(-1);
            send(currentBleedState.client_fd, err, strlen(err), 0);
            lua->popStack(1);
        } else {
            if (lua->luaGetTop() > 0) {
                const char* result = lua->luaToString(-1);
                if (result)
                    send(currentBleedState.client_fd, result, strlen(result), 0);
                lua->popStack(1);
            } else {
                const char* ok = "\nOK\n";
                send(currentBleedState.client_fd, ok, strlen(ok), 0);
            }
        }

        close(currentBleedState.client_fd);
    }



    return 0;
}

BleedStream::~BleedStream() {
    close(server_socket);
    delete lua;
}

