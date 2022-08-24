cmake_minimum_required(VERSION 3.22)
project(cxxit)

set(CMAKE_CXX_STANDARD 20)

add_executable(cxxit main.cpp)
include_directories(includes)

file(GLOB SOURCES_CODE sources/*.cpp)
add_library(cxxit_lib STATIC ${SOURCES_CODE})

find_package(fmt CONFIG REQUIRED)
find_package(folly CONFIG REQUIRED)

target_link_libraries(cxxit_lib fmt::fmt Folly::folly)
target_link_libraries(cxxit fmt::fmt Folly::folly cxxit_lib)
