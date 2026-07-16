// luah.h - Lua 5.4.6 header with auto library selection
#ifndef Lua_Include
extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"
}

// ---- auto-select library based on build configuration ----
// Path relative to .vcxproj directory (sibling to Jx3ZhuTools.sln)

#define LUA_LIB_REL "..\\lua-5.4.6\\lib\\"

#if defined(_DEBUG)
  #if defined(LUA_BUILD_AS_DLL)
    #define LUA_LIB_CFG "Debug_DLL"
  #else
    #define LUA_LIB_CFG "Debug_Static"
  #endif
  #define LUA_LIB_NAME "lua54d"
#else
  #if defined(LUA_BUILD_AS_DLL)
    #define LUA_LIB_CFG "Release_DLL"
  #else
    #define LUA_LIB_CFG "Release_Static"
  #endif
  #define LUA_LIB_NAME "lua54"
#endif

#if defined(_WIN64) || defined(_M_X64)
  #define LUA_LIB_PLATFORM "x64"
#else
  #define LUA_LIB_PLATFORM "Win32"
#endif

#define _LUA_PRAGMA_LIB(p) __pragma(comment(lib, p))
_LUA_PRAGMA_LIB(LUA_LIB_REL LUA_LIB_CFG "\\" LUA_LIB_PLATFORM "\\" LUA_LIB_NAME ".lib")

#undef LUA_LIB_REL
#undef LUA_LIB_CFG
#undef LUA_LIB_NAME
#undef LUA_LIB_PLATFORM
#undef _LUA_PRAGMA_LIB

#endif
