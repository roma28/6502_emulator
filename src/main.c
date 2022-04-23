// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 16.04.2022.
//

#include <stdio.h>
#include <stdlib.h>

#include "../include/6502_basic_structures.h"
#include "../include/6502_debug.h"
#include "../include/6502_utilities.h"
#include "../include/6502_instructions.h"
#include "../include/6502_decoder.h"



void nop(CPU *cpu) {
}


int main() {
    CPU cpu;
    cpu.RAM = malloc(RAM_SIZE * sizeof(uint8_t));
    if (cpu.RAM == NULL) return 1;

    FILE *romfile = fopen("../asm/a.out", "r");
    if (romfile) {
        load_ram(&cpu, romfile, 0x8000, 0x8000);
        fclose(romfile);
    }

    reset(&cpu);
    ssize_t instructions_to_run = 4;
    for (ssize_t i = 0; i < instructions_to_run; ++i) {
        decode(&cpu, fetch(&cpu));
        print_registers(&cpu);
    }

    FILE *ramfile = fopen("../asm/ram.bin", "w");
    if (ramfile) {
        dump_ram(&cpu, ramfile);
        fclose(ramfile);
    }
    return 0;
}


