// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include "../include/6502_utilities.h"

void reset(CPU *cpu) {
    cpu->reg.A = 0;
    cpu->reg.X = 0;
    cpu->reg.Y = 0;
    cpu->reg.SP = 0xfd;
    cpu->reg.PC = ((u_int8_t) *(cpu->RAM + 0xfffd) << 8) | ((u_int8_t) *(cpu->RAM + 0xffff));
    cpu->reg.P = 0b00110100;
}

void load_ram(CPU *cpu, FILE *f, size_t shift, size_t nbytes) {
    fread(cpu->RAM + shift, sizeof(uint8_t), nbytes, f);
}
