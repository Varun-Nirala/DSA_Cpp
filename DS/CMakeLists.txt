cmake_minimum_required(VERSION 3.20...3.31)

SET(PROJECT "DS")
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

#message(STATUS "SOURCE_DIR : ${SOURCE_DIR}")
#message(STATUS "COMMON_DIR : ${COMMON_DIR}")

include_directories(${SOURCE_DIR})

file(GLOB SRCS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cpp")
file(GLOB COMMON "${COMMON_DIR}/*.h" "${COMMON_DIR}/*.hpp" "${COMMON_DIR}/*.cpp")

#message(STATUS "SRCS : ${SRCS}")
#message(STATUS "COMMON : ${COMMON}")

source_group("" FILES ${SRCS})
source_group("Common" FILES ${COMMON})

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.cpp")

#message(STATUS "SOURCES : ${SOURCES}")

add_executable( ${PROJECT} ${SOURCES} )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT})

##Extra step to copy resources
#file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CONFIGURATION})

##Print all variable names
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#	message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()