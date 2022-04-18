cmake_minimum_required(VERSION 3.21)
project(6502emulator C)

set(CMAKE_C_STANDARD 99)

add_executable(6502emulator src/main.c src/6502_debug.c src/6502_instructions.c src/6502_utilities.c src/6502_decoder.c include/6502_decoder.h)
