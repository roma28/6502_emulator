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

void AND(CPU *cpu, uint8_t addressing_mode);

void ASL(CPU *cpu);

void BCC(CPU *cpu);

void BCS(CPU *cpu);

void BNE(CPU *cpu);

void BEQ(CPU *cpu);

void BPL(CPU *cpu);

void BMI(CPU *cpu);

void BVC(CPU *cpu);

void BVS(CPU *cpu);

void CLC(CPU *cpu);

void CLD(CPU *cpu);

void CLI(CPU *cpu);

void CLV(CPU *cpu);

void DEX(CPU *cpu);

void DEY(CPU *cpu);

void INX(CPU *cpu);

void INY(CPU *cpu);

void JMP(CPU *cpu, uint8_t addressing_mode);

void LDA(CPU *cpu, uint8_t addressing_mode);

void LDX(CPU *cpu, uint8_t addressing_mode);

void LDY(CPU *cpu, uint8_t addressing_mode);

void ORA(CPU *cpu, uint8_t addressing_mode);

void PHA(CPU *cpu);

void PLA(CPU *cpu);

void PHP(CPU *cpu);

void PLP(CPU *cpu);

void SEC(CPU *cpu);

void SED(CPU *cpu);

void SEI(CPU *cpu);

void STA(CPU *cpu, uint8_t addressing_mode);

void STX(CPU *cpu, uint8_t addressing_mode);

void STY(CPU *cpu, uint8_t addressing_mode);

void TAX(CPU *cpu);

void TXA(CPU *cpu);

void TAY(CPU *cpu);

void TYA(CPU *cpu);

void TSX(CPU *cpu);

void TXS(CPU *cpu);


#endif //INC_6502EMULATOR_6502_INSTRUCTIONS_H
