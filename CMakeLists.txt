cmake_minimum_required(VERSION 3.25)
set(TARGET_NAME battleship-tui)

#Set the Standard
set(CMAKE_CXX_STANDARD 17)

#Project instance
project(${TARGET_NAME} VERSION 1.0 LANGUAGES CXX)

#Setting up the sources and the header directory
set(SOURCES "src/main.cpp"
            "src/battleship.cpp"
            "src/exception.cpp")

#Creating the object files
add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC "header")
if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()