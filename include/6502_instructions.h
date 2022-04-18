// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#ifndef INC_6502EMULATOR_6502_INSTRUCTIONS_H
#define INC_6502EMULATOR_6502_INSTRUCTIONS_H
#include "6502_basic_structures.h"
#include "6502_decoder.h"

void ADC(CPU *cpu, uint8_t addressing_mode);

void CLC(CPU *cpu);

void INX(CPU *cpu);

void INY(CPU *cpu);

void LDA(CPU *cpu, uint8_t addressing_mode);

void LDX(CPU *cpu, uint8_t addressing_mode);

void LDY(CPU *cpu, uint8_t addressing_mode);

void ORA(CPU *cpu, uint8_t addressing_mode);

void STA(CPU *cpu, uint8_t addressing_mode);

#endif //INC_6502EMULATOR_6502_INSTRUCTIONS_H
