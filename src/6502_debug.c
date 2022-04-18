// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 17.04.2022.
//

#include "../include/6502_debug.h"

void print_registers(CPU *cpu) {
    printf("A: %02X\nX: %02X\nY: %02X\nSP: %04X\nPC: %04X\n", cpu->reg.A, cpu->reg.X, cpu->reg.Y, cpu->reg.SP,
           cpu->reg.PC);
    printf("Flags: ");
    for (int i = sizeof(uint8_t) * 8; i != -1; i--) printf("%d", (cpu->reg.P & (1 << i)) >> i);
}

int dump_ram(CPU *cpu, FILE *f) {
    size_t written = fwrite(cpu->RAM, sizeof(uint8_t), 0xffff, f);
    fclose(f);
    if (written == 0xffff) return 0;
    return 1;
}

void load_ram(CPU *cpu, FILE *f, size_t shift, size_t nbytes) {
    fread(cpu->RAM + shift, sizeof(uint8_t), nbytes, f);
}

void reset(CPU *cpu) {
    cpu->reg.A = 0;
    cpu->reg.X = 0;
    cpu->reg.Y = 0;
    cpu->reg.SP = 0x01ff;
    cpu->reg.PC = ((u_int8_t) *(cpu->RAM + 0xfffd) << 8) | ((u_int8_t) *(cpu->RAM + 0xffff));
    cpu->reg.P = 0b00110100;
};


