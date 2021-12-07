project(lua_2.4)
cmake_minimum_required(VERSION 2.18)

include_directories(.)

add_library(lualib fallback.c
                   func.c
                   hash.c
                   inout.c
                   lex.c
                   mem.c
                   opcode.c
                   parser.c
                   table.c
                   tree.c
                   undump.c)

add_executable(lua lua.c
                   iolib.c
                   mathlib.c
                   strlib.c)

add_executable(luac luac.c
                    print.c
                    dump.c)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua m)
  target_link_libraries(luac m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

target_link_libraries(lua lualib)
target_link_libraries(luac lualib)