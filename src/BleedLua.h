//
// Created by Praveen P on 26-10-2025.
//

#ifndef BLEED_BLEEDLUA_H
#define BLEED_BLEEDLUA_H

#include "../include/lua/lua.hpp"
#include <android/log.h>

class BleedLua {
    lua_State *L;


    public:
    BleedLua();
    ~BleedLua();
    int execString(const char* code);
    lua_State *getLuaState();
    void dumpStack();
};


#endif //BLEED_BLEEDLUA_H