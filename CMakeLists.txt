project(lua_4.0.1)
cmake_minimum_required(VERSION 2.18)

include_directories(.
                    ../cJSON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  SET(CXX_FLAGS )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  SET(CXX_FLAGS
                /Od
                /D "WIN32"
                /D "_DEBUG"
                /ZI
                /MTd
                /DEBUG)
endif()

add_library(lualib lapi.c
                   lcode.c
                   ldo.c
                   ldebug.c
                   lfunc.c
                   lgc.c
                   llex.c
                   lmem.c
                   lobject.c
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
                   lstrlib.c
                   ljsonlib.c)

add_executable(luac luac.c
                    dump.c
                    opt.c
                    print.c
                    lauxlib.c)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua m)
  target_link_libraries(luac m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

target_link_libraries(lua lualib cjson)
target_link_libraries(luac lualib cjson)

add_subdirectory(cJSON)