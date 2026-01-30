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
    lua_register(L, "testMod", testMod);
}

int BleedLua::testMod(lua_State *L) {
    printf("test");
    return 0;
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


    if ( B_readmem(offset, buf, size) != 0) {
        free(buf);
        return luaL_error(L, "read failed");
    }

    lua_pushlstring(L, buf, size);

    free(buf);
    return 1;
}


int BleedLua::B_readmem(long long offset, void* buf, int size) {

    unsigned char vec;

    // if (mincore(offset, size, &vec ))

    memcpy(buf, (void*)offset, size);


    return 0;
}


int BleedLua::writeMemory(lua_State *L) {

    long long address = luaL_checkinteger(L, 1);

    size_t size;
    const char* data = luaL_checklstring(L, 2, &size);

    if (B_writemem(address, data, (int)size) != 0)
        return luaL_error(L, "memory write failed");

    return 0;
}


int BleedLua::B_writemem(long long address, const void* data, int size) {
    if (!data || size <= 0 || address == 0)
        return -1;

    long pageSize = sysconf(_SC_PAGESIZE); // usually 4096
    void* pageStart = (void*)(address & ~(pageSize - 1));

    if (mprotect(pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
        return -2;

    memcpy((void*)address, data, size);

    return 0;
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

