cmake_minimum_required(VERSION 3.4)

project(NANATest)

# add_subdirectory(ext)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -static)

file(GLOB SOURCE *.cpp)
file(GLOB HEADER *.h)

set(NANA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/nana CACHE PATH "")

if (NOT EXISTS "${NANA_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "Please specify valid nana path!")
endif ()

add_subdirectory(${NANA_PATH})

add_executable(NANATest ${SOURCE} ${HEADER})
target_link_libraries(NANATest nana)