project(lua_1.0)
cmake_minimum_required(VERSION 2.18)

include_directories(.)

add_executable(lua hash.c inout.c iolib.c lex_yy.c lua.c mathlib.c opcode.c strlib.c table.c y_tab.c)