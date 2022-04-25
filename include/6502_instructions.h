// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#ifndef INC_6502EMULATOR_6502_INSTRUCTIONS_H
#define INC_6502EMULATOR_6502_INSTRUCTIONS_H

#include "6502_basic_structures.h"
#include "6502_decoder.h"

/**
 * ADd memory to accumulator with Carry
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void ADC(CPU *cpu, uint8_t addressing_mode);

/**
 * AND memory with accumulator
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void AND(CPU *cpu, uint8_t addressing_mode);

/**
 * Accumulator Shift Left
 * @param cpu pointer to a CPU instance
 */
void ASL(CPU *cpu);

/**
 * Branch on Carry Clear
 * @param cpu pointer to a CPU instance
 */
void BCC(CPU *cpu);

/**
 * Branch on Carry Set
 * @param cpu pointer to a CPU instance
 */
void BCS(CPU *cpu);

/**
 * Branch on Non-Equal
 * @param cpu pointer to a CPU instance
 */
void BNE(CPU *cpu);

/**
 * Branch on EQual
 * @param cpu pointer to a CPU instance
 */
void BEQ(CPU *cpu);

/**
 * Branch on PLus
 * @param cpu pointer to a CPU instance
 */
void BPL(CPU *cpu);

/**
 * Branch on MInus
 * @param cpu pointer to a CPU instance
 */
void BMI(CPU *cpu);

/**
 * Branch on oVerflow Clear
 * @param cpu pointer to a CPU instance
 */
void BVC(CPU *cpu);

/**
 * Branch on oVerflow Set
 * @param cpu pointer to a CPU instance
 */
void BVS(CPU *cpu);

/**
 * CLear Carry
 * @param cpu pointer to a CPU instance
 */
void CLC(CPU *cpu);

/**
 * CLear Decimal
 * @param cpu pointer to a CPU instance
 */
void CLD(CPU *cpu);

/**
 * CLear Interrupt
 * @param cpu pointer to a CPU instance
 */
void CLI(CPU *cpu);

/**
 * CLear oVerflow
 * @param cpu pointer to a CPU instance
 */
void CLV(CPU *cpu);

/**
 * DECrement memory
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void DEC(CPU *cpu, uint8_t addressing_mode);

/**
 * DEcrement X
 * @param cpu pointer to a CPU instance
 */
void DEX(CPU *cpu);

/**
 * DEcrement Y
 * @param cpu pointer to a CPU instance
 */
void DEY(CPU *cpu);

/**
 * Exclusive OR accumulator and memory
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void EOR(CPU *cpu, uint8_t addressing_mode);

/**
 * INCrement memory
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void INC(CPU *cpu, uint8_t addressing_mode);

/**
 * INcrement X
 * @param cpu pointer to a CPU instance
 */
void INX(CPU *cpu);

/**
 * INcrement Y
 * @param cpu pointer to a CPU instance
 */
void INY(CPU *cpu);

void JMP(CPU *cpu, uint8_t addressing_mode);

/**
 * Jump SubRoutine
 * @param cpu pointer to a CPU instance
 */
void JSR(CPU *cpu);

/**
 * LoaD A
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void LDA(CPU *cpu, uint8_t addressing_mode);

/**
 * LoaD X
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void LDX(CPU *cpu, uint8_t addressing_mode);

/**
 * LoaD Y
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void LDY(CPU *cpu, uint8_t addressing_mode);

/**
 * OR Accumulator with memory
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void ORA(CPU *cpu, uint8_t addressing_mode);

/**
 * PusH Accumulatorr
 * @param cpu pointer to a CPU instance
 */
void PHA(CPU *cpu);

/**
 * PulL Accumulator
 * @param cpu pointer to a CPU instance
 */
void PLA(CPU *cpu);

/**
 * PusH P
 * @param cpu pointer to a CPU instance
 */
void PHP(CPU *cpu);

/**
 * PulL P
 * @param cpu pointer to a CPU instance
 */
void PLP(CPU *cpu);

/**
 * ReTurn from Subroutine
 * @param cpu pointer to a CPU instance
 */
void RTS(CPU *cpu);

/**
 * SEt Carry
 * @param cpu pointer to a CPU instance
 */
void SEC(CPU *cpu);

/**
 * SEt Decimal
 * @param cpu pointer to a CPU instance
 */
void SED(CPU *cpu);

/**
 * SEt Interrupt
 * @param cpu pointer to a CPU instance
 */
void SEI(CPU *cpu);

/**
 * STore A
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void STA(CPU *cpu, uint8_t addressing_mode);

/**
 * STore X
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void STX(CPU *cpu, uint8_t addressing_mode);

/**
 * STore Y
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 */
void STY(CPU *cpu, uint8_t addressing_mode);

/**
 * Transfer A to X
 * @param cpu pointer to a CPU instance
 */
void TAX(CPU *cpu);

/**
 * Transfer A to X
 * @param cpu pointer to a CPU instance
 */
void TXA(CPU *cpu);

/**
 * Transfer A to Y
 * @param cpu pointer to a CPU instance
 */
void TAY(CPU *cpu);

/**
 * Transfer Y to A
 * @param cpu pointer to a CPU instance
 */
void TYA(CPU *cpu);

/**
 * Transfer Stack pointer to X
 * @param cpu pointer to a CPU instance
 */
void TSX(CPU *cpu);

/**
 * Transfer X to Stack pointer
 * @param cpu pointer to a CPU instance
 */
void TXS(CPU *cpu);

#endif //INC_6502EMULATOR_6502_INSTRUCTIONS_H
