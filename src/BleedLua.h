//
// Created by Praveen P on 26-10-2025.
//

#ifndef BLEED_BLEEDLUA_H
#define BLEED_BLEEDLUA_H

#include "../include/lua/lua.hpp"
#include <android/log.h>
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>
#include <string.h>
#include <sys/mman.h>

class BleedLua {
    lua_State *L;


    public:
    BleedLua();
    ~BleedLua();
    int execString(const char* code);
    lua_State *getLuaState();
    void popStack(int n);
    const char* luaToString(signed int n);
    int luaGetTop();
    static int readMemory(lua_State *L);
    static int writeMemory(lua_State *L);
    static int readMaps(lua_State *L);
    static int luaPrint(lua_State *L);

    static int B_readmem(long long offset, void* buf, int size);
    static int B_writemem(long long address, const void* data, int size);

};


#endif //BLEED_BLEEDLUA_H