// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 17.04.2022.
//
#include <stdlib.h>

#ifndef INC_6502EMULATOR_6502_BASIC_STRUCTURES_H
#define INC_6502EMULATOR_6502_BASIC_STRUCTURES_H
typedef struct CPU CPU;

typedef enum {
    CARRY = (1 << 0),
    ZERO = (1 << 1),
    IRQ = (1 << 2),
    DECIMAL = (1 << 3),
    BRK = (1 << 4),
    OVERFLOW = (1 << 6),
    NEGATIVE = (1 << 7)
} flags;

typedef enum {
    ABSOLUTE,
    ABSOLUTE_INDEXED_INDIERCT,
    ABSOLUTE_INDEXED_X,
    ABSOLUTE_INDEXED_Y,
    ABSOLUTE_INDIRECT,
    ACCUMULATOR,
    IMMEDIATE,
    IMPLIED,
    PROGRAM_COUNTER_RELATIVE,
    STACK,
    ZERO_PAGE
} addressing;


struct registers {
    u_int8_t A;
    u_int8_t X;
    u_int8_t Y;
    u_int16_t SP;
    u_int16_t PC;
    u_int8_t P;
};

struct CPU {
    struct registers reg;
    u_int8_t *RAM;
};

#endif //INC_6502EMULATOR_6502_BASIC_STRUCTURES_H
