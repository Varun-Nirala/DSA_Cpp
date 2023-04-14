cmake_minimum_required(VERSION 3.14)

SET(PROJECT "Threads")
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

file(GLOB PR_HEADER_FILES "includes/*.h")
file(GLOB PR_SOURCE_FILES "src/*.cpp")

set(SOURCE_FILES
	${PR_HEADER_FILES}
	${PR_SOURCE_FILES}
	)

source_group("Header Files" FILES ${PR_HEADER_FILES})
source_group("Source Files" FILES ${PR_SOURCE_FILES})

file(GLOB LOCAL_INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_CURRENT_LIST_DIR}/includes")
include_directories(${LOCAL_INCLUDE_PATHS})

add_executable( ${PROJECT} ${SOURCE_FILES} )