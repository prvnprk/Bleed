//
// Created by Praveen P on 26-10-2025.
//

#include "BleedLua.h"



BleedLua::BleedLua() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

BleedLua::~BleedLua() {
    lua_close(L);
}

int BleedLua::execString(const char* code) {
    int strret = luaL_dostring(L,code);
    dumpStack();
    lua_settop(L, 0); //clear stack

    return strret;
}

lua_State* BleedLua::getLuaState() {
    return L;
}

void BleedLua::dumpStack() {
    int top=lua_gettop(L);
    for (int i=1; i <= top; i++) {
        __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK TYPE: ","%d\t%s\t", i, luaL_typename(L,i));
        switch (lua_type(L, i)) {
            case LUA_TNUMBER:
                __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK ","%g\n",lua_tonumber(L,i));
                break;
            case LUA_TSTRING:
                __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK ","%s\n",lua_tostring(L,i));
                break;
            case LUA_TBOOLEAN:
                __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK ","%s\n", (lua_toboolean(L, i) ? "true" : "false"));
                break;
            case LUA_TNIL:
                __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK ","%s\n", "nil");
                break;
            default:
                __android_log_print(ANDROID_LOG_VERBOSE, "LUASTACK ","%p\n",lua_topointer(L,i));
                break;
        }
    }
}