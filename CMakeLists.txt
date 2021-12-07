project(lua_3.0)
cmake_minimum_required(VERSION 2.18)

include_directories(.)

add_library(lualib fallback.c
                   func.c
                   hash.c
                   inout.c
                   lex.c
                   luamem.c
                   opcode.c
                   parser.c
                   table.c
                   tree.c
                   undump.c
                   zio.c)

add_executable(lua lua.c
                   iolib.c
                   mathlib.c
                   strlib.c
                   auxlib.c)

add_executable(luac luac.c
                    print.c
                    dump.c
                    auxlib.c)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua m)
  target_link_libraries(luac m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

target_link_libraries(lua lualib)
target_link_libraries(luac lualib)