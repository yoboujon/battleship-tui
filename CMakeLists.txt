cmake_minimum_required(VERSION 3.1...3.25)
set(TARGET_NAME battleship-tui)
set (CMAKE_CXX_STANDARD 17)

project(
    ${TARGET_NAME}
    VERSION 1.0
    LANGUAGES CXX)

#Setting up the sources and the header directory
set(SOURCES "src/main.cpp")
include_directories("header")

#Creating the object files
add_executable(${TARGET_NAME} ${SOURCES})

#To ensure that warnings are present when compiling
if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()