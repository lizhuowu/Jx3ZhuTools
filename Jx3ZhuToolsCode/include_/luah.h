// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++
#ifndef Lua_Include
extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"
	#pragma comment (lib,"lib\\lua.lib")
};
#endif 
