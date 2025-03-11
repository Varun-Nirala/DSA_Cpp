cmake_minimum_required(VERSION 3.20...3.31)

SET(PROJECT "STL_style_DS")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(COMMON_DIR ${SOURCE_DIR}/Common)
set(D_ARR_DIR ${SOURCE_DIR}/DynamicArray)
set(DP_DIR ${SOURCE_DIR}/DynamicProgramming)
set(GRAPH_DIR ${SOURCE_DIR}/Graph)
set(LIST_DIR ${SOURCE_DIR}/List)
set(SEARCHING_DIR ${SOURCE_DIR}/Searching)
set(SMARTPTR_DIR ${SOURCE_DIR}/SmartPointer)
set(SORTING_DIR ${SOURCE_DIR}/Sorting)
set(TREE_DIR ${SOURCE_DIR}/Tree)


include_directories(${SOURCE_DIR})
#include_directories(${D_ARR_DIR})
#include_directories(${DP_DIR})
#include_directories(${GRAPH_DIR})
#include_directories(${LIST_DIR})
#include_directories(${SEARCHING_DIR})
#include_directories(${SMARTPTR_DIR})
#include_directories(${SORTING_DIR})
#include_directories(${TREE_DIR})

file(GLOB SRCS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cpp")
file(GLOB COMMON "${COMMON_DIR}/*.h" "${COMMON_DIR}/*.hpp" "${COMMON_DIR}/*.cpp")
file(GLOB D_ARR "${D_ARR_DIR}/*.h" "${D_ARR_DIR}/*.hpp" "${D_ARR_DIR}/*.cpp")
file(GLOB DP "${DP_DIR}/*.h" "${DP_DIR}/*.hpp" "${DP_DIR}/*.cpp")
file(GLOB GRAPH "${GRAPH_DIR}/*.h" "${GRAPH_DIR}/*.hpp" "${GRAPH_DIR}/*.cpp")
file(GLOB LIST "${LIST_DIR}/*.h" "${LIST_DIR}/*.hpp" "${LIST_DIR}/*.cpp")
file(GLOB SEARCHING "${SEARCHING_DIR}/*.h" "${SEARCHING_DIR}/*.hpp" "${SEARCHING_DIR}/*.cpp")
file(GLOB SMARTPTR "${SMARTPTR_DIR}/*.h" "${SMARTPTR_DIR}/*.hpp" "${SMARTPTR_DIR}/*.cpp")
file(GLOB SORTING "${SORTING_DIR}/*.h" "${SORTING_DIR}/*.hpp" "${SORTING_DIR}/*.cpp")
file(GLOB TREE "${TREE_DIR}/*.h" "${TREE_DIR}/*.hpp" "${TREE_DIR}/*.cpp")

source_group("" FILES ${SRCS})
source_group("Common" FILES ${COMMON})
source_group("DynamicArray" FILES ${D_ARR})
source_group("DynamicProgramming" FILES ${DP})
source_group("Graph" FILES ${GRAPH})
source_group("List" FILES ${LIST})
source_group("Searching" FILES ${SEARCHING})
source_group("SmartPointer" FILES ${SMARTPTR})
source_group("Sorting" FILES ${SORTING})
source_group("Tree" FILES ${TREE})

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.cpp")

add_executable( ${PROJECT} ${SOURCES} )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})