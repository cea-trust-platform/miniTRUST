cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

project(miniTRUST CXX)

enable_testing()

set(TRUST_ROOT ${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_definitions(-D_COMPILE_AVEC_GCC_)

add_subdirectory(src)

set(tgt_obj)
# sub_parts variable is defined in src:
include(src/obj_lst.cmake)
foreach(_bit ${sub_parts})
   set(tgt_obj ${tgt_obj} $<TARGET_OBJECTS:${_bit}>)
endforeach()

add_executable(miniTRUST ${tgt_obj})


add_test(NAME conduc COMMAND ${CMAKE_SOURCE_DIR}/tests/basic/conduc.sh  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/basic)

