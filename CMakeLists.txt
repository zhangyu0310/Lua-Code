project(lua_1.1)
cmake_minimum_required(VERSION 2.18)

include_directories(include
                    src
					clients/lib
					clients/lua)
					
aux_source_directory(src SRC)
aux_source_directory(clients/lib LUA_LIB)
aux_source_directory(clients/lua LUA)

add_library(liblua ${SRC})

add_executable(lua ${LUA} ${LUA_LIB})

target_link_libraries(lua liblua)