project(lua_1.1)
cmake_minimum_required(VERSION 2.18)

include_directories(include
                    src
                    clients/lib
                    clients/lua)
					
aux_source_directory(src SRC)
aux_source_directory(clients/lib LUA_LIB)
aux_source_directory(clients/lua LUA)

add_library(lua11 ${SRC})

add_executable(lua ${LUA} ${LUA_LIB})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua lua11 m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  target_link_libraries(lua lua11)
endif()

