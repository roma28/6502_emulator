// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <stdio.h>
#include <stdlib.h>

#include "../include/6502_basic_structures.h"

void reset(CPU *cpu) {
    cpu->reg.A = 0;
    cpu->reg.X = 0;
    cpu->reg.Y = 0;
    cpu->reg.S = 0x01ff;
    cpu->reg.PC = ((u_int8_t) *(cpu->RAM + 0xfffd) << 8) + ((u_int8_t) *(cpu->RAM + 0xffff));
    cpu->reg.P = 0b00110100;
};

int dump_ram(CPU *cpu) {
    FILE *of = fopen("ram_dump.bin", "w");

    if (of != NULL) {
        size_t written = fwrite(cpu->RAM,  sizeof(uint8_t), 0xffff, of);
        fclose(of);
        if (written == 0xffff) return 0;
    }
    return 1;
}

void nop(CPU *cpu) {
}

void load_ram(CPU *cpu, FILE *f) {
    fread(cpu->RAM + 0x8000, sizeof(uint8_t), 0x8000, f);
}

void print_registers(CPU *cpu) {
    printf("A: %X\nX: %X\nY: %X\nPC: %04X\n", cpu->reg.A, cpu->reg.X, cpu->reg.Y, cpu->reg.PC);
    printf("Flags: ");
    for (int i = sizeof(uint8_t) * 8; i != -1; i--) printf("%d", (cpu->reg.P & (1 << i)) >> i);
}


int main() {
    CPU cpu;
    cpu.RAM = malloc(65536 * sizeof(uint8_t));
    if (cpu.RAM == NULL) return 1;

    FILE *romfile = fopen("../asm/a.out", "r");
    if (romfile != NULL) {
        load_ram(&cpu, romfile);
        fclose(romfile);
    }

    reset(&cpu);
    print_registers(&cpu);

    dump_ram(&cpu);
    return 0;
}

