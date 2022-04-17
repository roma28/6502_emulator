// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef INC_6502EMULATOR_6502_BASIC_STRUCTURES_H
#define INC_6502EMULATOR_6502_BASIC_STRUCTURES_H
typedef struct CPU CPU;

enum flags {
    CARRY = (1 << 0),
    ZERO = (1 << 1),
    IRQ = (1 << 2),
    DECIMAL = (1 << 3),
    BRK = (1 << 4),
    OVERFLOW = (1 << 6),
    NEGATIVE = (1 << 7)
};

struct registers {
    u_int8_t A;
    u_int8_t X;
    u_int8_t Y;
    u_int8_t S;
    u_int16_t PC;
    u_int8_t P;
};

struct CPU {
    struct registers reg;
    u_int8_t *RAM;
};

#endif //INC_6502EMULATOR_6502_BASIC_STRUCTURES_H