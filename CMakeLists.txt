cmake_minimum_required(VERSION 3.21)
project(6502emulator C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_library(6502emulator include/6502_basic_structures.h src/6502_debug.c src/6502_instructions.c src/6502_utilities.c src/6502_decoder.c)
target_link_libraries(6502emulator)


add_executable(main src/main.c src/terminal.c)
target_link_libraries(main 6502emulator ${CURSES_LIBRARIES})
