cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

project(miniTRUST CXX)

##
## Always build in Debug for now
##
set(CMAKE_BUILD_TYPE Debug)

enable_testing()

set(TRUST_ROOT ${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_definitions(-D_COMPILE_AVEC_GCC_)

##
## Kokkos support
##
add_definitions(-DKOKKOS_)

cmake_policy(SET CMP0074 NEW)
find_package(Kokkos REQUIRED)
set(Kokkos_INCL $ENV{KOKKOS_ROOT_DIR}/include)
include_directories(${Kokkos_INCL})
message("hello Kokkos: ${Kokkos_INCL}")

add_subdirectory(src)

set(tgt_obj)
# sub_parts variable is defined in src:
include(src/obj_lst.cmake)
foreach(_bit ${sub_parts})
   set(tgt_obj ${tgt_obj} $<TARGET_OBJECTS:${_bit}>)
endforeach()

add_executable(miniTRUST ${tgt_obj})
target_link_libraries(miniTRUST Kokkos::kokkos)

add_test(NAME conduc COMMAND ${CMAKE_SOURCE_DIR}/tests/basic/conduc.sh  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/basic)
