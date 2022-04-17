// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <stdio.h>
#include <stdlib.h>

#include "../include/6502_basic_structures.h"

void reset(CPU *cpu) {
    cpu->reg.A = 0;
    cpu->reg.X = 0;
    cpu->reg.Y = 0;
    cpu->reg.S = 0;
    cpu->reg.PC = 0xfdfc;
    cpu->reg.P = 0b00110100;
};

int main() {
    CPU cpu;
    cpu.RAM = malloc(65536 * sizeof(uint8_t));
    if(cpu.RAM == NULL) return 1;

    reset(&cpu);

    return 0;
};

