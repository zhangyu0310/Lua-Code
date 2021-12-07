project(lua_2.1)
cmake_minimum_required(VERSION 2.18)

include_directories(.)

aux_source_directory(. SRC)

add_executable(lua ${SRC})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  target_link_libraries(lua m)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()