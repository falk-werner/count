cmake_minimum_required(VERSION 3.10)
project(count)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(count src/main.cpp)

install(TARGETS count DESTINATION bin)