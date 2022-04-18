// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 16.04.2022.
//

#include <stdio.h>
#include <stdlib.h>

#include "../include/6502_basic_structures.h"
#include "../include/6502_debug.h"


void nop(CPU *cpu) {
}

int main() {
    CPU cpu;
    cpu.RAM = malloc(65536 * sizeof(uint8_t));
    if (cpu.RAM == NULL) return 1;

    FILE *romfile = fopen("../asm/a.out", "r");
    if (romfile) {
        load_ram(&cpu, romfile, 0x8000, 0x8000);
        fclose(romfile);
    }

    reset(&cpu);
    print_registers(&cpu);

    FILE *ramfile = fopen("../asm/ram.bin", "r");
    if (ramfile) {
        dump_ram(&cpu, ramfile);
        fclose(ramfile);
    }
    return 0;
}

