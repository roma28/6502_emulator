// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include "../include/6502_utilities.h"

/**
 * Resets CPU to its default state
 * @param cpu pointer to a CPU instance
 */
void reset(CPU *cpu) {
    cpu->reg.A = 0;
    cpu->reg.X = 0;
    cpu->reg.Y = 0;
    cpu->reg.SP = 0xfd;
    cpu->reg.PC = cpu->MEM[0xfffd] << 8 | cpu->MEM[0xfffc];
    cpu->reg.P = 0b00110100;
}

/**
 * Loads MEM from a file
 * @param cpu pointer to a CPU instance
 * @param f file to load from
 * @param shift shift in MEM to load file
 * @param nbytes number of bytes to load to MEM
 */
void load_mem(CPU *cpu, FILE *f, size_t shift, size_t nbytes) {
    fread(cpu->MEM + shift, sizeof(uint8_t), nbytes, f);
}
