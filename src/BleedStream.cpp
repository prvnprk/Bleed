//
// Created by Praveen P on 01-11-2025.
//

#include "BleedStream.h"



BleedStream::BleedStream() {
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

    BleedLua *lua = new BleedLua();



    lua_State* L = lua->getLuaState();

    printf("serverloop\n");


    while (true) {
        sockaddr_in client{};
        socklen_t client_size = sizeof(client);
        int client_fd = accept(server_socket, (sockaddr*)&client, &client_size);
        if (client_fd == -1) { perror("accept"); continue; }

        char buffer[4096];
        ssize_t bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) { close(client_fd); continue; }

        buffer[bytes] = 0;
        std::cout << "Executing: " << buffer << "\n";

        if (lua->execString(buffer) != LUA_OK) {
            const char* err = lua_tostring(L, -1);
            send(client_fd, err, strlen(err), 0);
            lua_pop(L, 1);
        } else {

            if (lua_gettop(L) > 0) {
                const char* result = lua_tostring(L, -1);
                if (result)
                    send(client_fd, result, strlen(result), 0);
                lua_pop(L, 1);
            } else {
                const char* ok = "OK";
                send(client_fd, ok, strlen(ok), 0);
            }
        }

        close(client_fd);


    }
    lua_close(L);

    return 0;
}

BleedStream::~BleedStream() {
    close(server_socket);
}

