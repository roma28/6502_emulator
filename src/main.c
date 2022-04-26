// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 16.04.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "../include/6502_basic_structures.h"
#include "../include/6502_debug.h"
#include "../include/6502_utilities.h"
#include "../include/6502_instructions.h"
#include "../include/6502_decoder.h"


void nop(CPU *cpu) {
}


int main() {
    CPU cpu;
    cpu.MEM = (uint8_t *) malloc(RAM_SIZE * sizeof(uint8_t));
    if (cpu.MEM == NULL) return 1;

    FILE *memfile = fopen("../asm/a.out", "r");
    if (memfile) {
        load_mem(&cpu, memfile, 0x8000, 0x8000);
        fclose(memfile);
    }

    reset(&cpu);
//    ssize_t instructions_to_run = INT32_MAX;
//    ssize_t instructions_to_run = 25;
//    for (ssize_t i = 0; i < instructions_to_run; ++i) {
//        decode(&cpu, fetch(&cpu));
////        print_registers(&cpu);
//    }

    print_registers(&cpu);
    uint8_t opcode = fetch(&cpu);
    int i = 0;
    while (opcode != 0) {
        print_registers(&cpu);
        decode(&cpu, opcode);
        opcode = fetch(&cpu);
        i++;
    };

    FILE *ramfile = fopen("../asm/ram.bin", "w");
    if (ramfile) {
        dump_ram(&cpu, ramfile);
        fclose(ramfile);
    }
    printf("%d instructions executed", i);

    return 0;
}


