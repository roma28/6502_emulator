// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 17.04.2022.
//

#include "../include/6502_debug.h"

/**
 * Produces a nice print of CPU state to stdout
 * @param cpu pointer to a CPU instance
 */
void print_registers(CPU *cpu) {
    printf("A: %02X\nX: %02X\nY: %02X\nSP: %04X\nPC: %04X\n", cpu->registers.A, cpu->registers.X, cpu->registers.Y,
           cpu->registers.SP,
           cpu->registers.PC);
    printf("Flags: ");
    for (int i = sizeof(uint8_t) * 8; i != -1; i--) printf("%d", (cpu->registers.P & (1 << i)) >> i);
    printf("\n\n");
}

/**
 * Writes all MEM contents to file
 * @param cpu pointer to a CPU instance
 * @param file file to write MEM contents
 */
int dump_ram(CPU *cpu, FILE *f) {
    size_t written = fwrite(cpu->MEM, sizeof(uint8_t), RAM_SIZE, f);
    fclose(f);
    if (written == 0xffff) return 0;
    return 1;
}




