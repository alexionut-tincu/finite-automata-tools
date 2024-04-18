cmake_minimum_required(VERSION 3.5)

project(finite-automata-tools)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(finite-automata-tools ${SOURCES})

target_include_directories(finite-automata-tools PUBLIC include)

target_link_libraries(finite-automata-tools)

install(TARGETS finite-automata-tools DESTINATION bin)

