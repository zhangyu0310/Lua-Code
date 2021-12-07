project(lua_5.1.5)
cmake_minimum_required(VERSION 2.18)

include_directories(.)

add_library(lualib lapi.c
                   lcode.c
                   ldo.c
                   ldump.c
                   ldebug.c
                   lfunc.c
                   lgc.c
                   llex.c
                   lmem.c
                   lobject.c
                   lopcodes.c
                   lparser.c
                   lstate.c
                   lstring.c
                   ltable.c
                   ltm.c
                   lundump.c
                   lvm.c
                   lzio.c)

add_executable(lua lua.c
                   lauxlib.c
                   lbaselib.c
                   ldblib.c
                   liolib.c
                   lmathlib.c
                   loslib.c
                   ltablib.c
                   lstrlib.c
                   loadlib.c
                   linit.c)

add_executable(luac luac.c
                    print.c
                    lauxlib.c)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua m)
  target_link_libraries(luac m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

target_link_libraries(lua lualib)
target_link_libraries(luac lualib)