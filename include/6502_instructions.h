// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//
#include "6502_basic_structures.h"
#ifndef INC_6502EMULATOR_6502_INSTRUCTIONS_H
#define INC_6502EMULATOR_6502_INSTRUCTIONS_H
void ADC(CPU *cpu, uint8_t addressing_mode);

void LDA(CPU *cpu, uint8_t addressing_mode);

void STA(CPU *cpu, uint8_t addressing_mode);
#endif //INC_6502EMULATOR_6502_INSTRUCTIONS_H
