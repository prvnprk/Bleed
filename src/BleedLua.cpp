//
// Created by Praveen P on 26-10-2025.
//

#include "BleedLua.h"

#include <unistd.h>


#include "states.h"


BleedLua::BleedLua() {
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "readMem", readMemory);
    lua_register(L, "writeMem", writeMemory);
    lua_register(L, "readMaps", readMaps);
    lua_register(L, "print", luaPrint);
}

int BleedLua::luaPrint(lua_State *L) {
    size_t len;
    const char *buf = luaL_checklstring(L, 1, &len);


    send(currentBleedState.client_fd, buf, len, 0);

    lua_pushlstring(L, buf, len);

    return 1;
}


int BleedLua::readMemory(lua_State *L) {

    int size = luaL_checkinteger(L, 1);
    long long offset = luaL_checkinteger(L, 2);



    char* buf = (char*)malloc(size);



    if (!buf)
        return luaL_error(L, "malloc failed");


    memcpy(buf, (void *)offset, size);




    // ssize_t bytes_read = pread(currentBleedState.mem, buf, size, offset);
    //
    // if (bytes_read < 0) {
    //     free(buf);
    //     return luaL_error(L, "pread failed");
    // }
    //
    // printf("Read %d bytes\n", bytes_read);
    // //
    // // for (int i = 0; i < bytes_read; i++) {
    // //     printf("%x ", buf[i]);
    // // }


    // lua_pushlstring(L, buf, bytes_read);
    lua_pushlstring(L, buf, size);

    free(buf);
    return 1;
}

int BleedLua::writeMemory(lua_State *L) {

}

int BleedLua::readMaps(lua_State *L) {

    std::stringstream mapsstream;

    mapsstream << currentBleedState.mem_maps.rdbuf();

    lua_pushlstring(L, mapsstream.str().c_str(), mapsstream.str().size());

    currentBleedState.mem_maps.clear();
    currentBleedState.mem_maps.seekg(0);

    return 1;

}



BleedLua::~BleedLua() {
    lua_close(L);
}

int BleedLua::execString(const char* code) {
    int strret = luaL_dostring(L,code);

    return strret;
}

lua_State* BleedLua::getLuaState() {
    return L;
}



void BleedLua::popStack(int n) {
    lua_pop(L, n);
}

const char* BleedLua::luaToString(signed int n) {
    return lua_tostring(L,n);
}

int BleedLua::luaGetTop() {
    return lua_gettop(L);
}

