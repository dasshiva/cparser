cmake_minimum_required(VERSION 3.20.0)
project(lang VERSION 0.0.1)

file(GLOB_RECURSE LANGC_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
set(LANGC_INCLUDE_DIRS "include/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(langc ${LANGC_SOURCES})
target_include_directories(langc PRIVATE LANGC_INCLUDE_DIRS)
