// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 17.04.2022.
//

#include "6502_basic_structures.h"
#include <stdio.h>

#ifndef INC_6502EMULATOR_6502_DEBUG_H
#define INC_6502EMULATOR_6502_DEBUG_H

int dump_ram(CPU *cpu, FILE *f);

void print_registers(CPU *cpu);


#endif //INC_6502EMULATOR_6502_DEBUG_H
