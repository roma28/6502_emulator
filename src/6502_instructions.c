// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include <stdio.h>
#include "../include/6502_instructions.h"

void set_flags(CPU *cpu, uint8_t result) {
    if (result == 0) cpu->reg.P |= ZERO;
    if (result & 0b10000000) cpu->reg.P |= NEGATIVE;
}

void ADC(CPU *cpu, uint8_t addressing_mode) {
    //ADd memory to accumulator with Carry
    uint8_t operand = get_operand(cpu, addressing_mode);

    uint8_t res = cpu->reg.A + operand;
    res += cpu->reg.P & 1; // checking for carry flag

    cpu->reg.A = res;
}

void AND(CPU *cpu, uint8_t addressing_mode) {
    //Accumulator aND
    cpu->reg.A &= get_operand(cpu, addressing_mode);
}

void ASL(CPU *cpu) {
    //Accumulator Shift Left
    cpu->reg.A <<= 1;
}

void BCC(CPU *cpu) {
    //Branch on Carry Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->reg.P & CARRY)) cpu->reg.PC = branch_address;
}

void BCS(CPU *cpu) {
    //Branch on Carry Set
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->reg.P & CARRY) cpu->reg.PC = branch_address;
}

void BNZ(CPU *cpu) {
    //Branch on Non-Zero
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->reg.P & ZERO)) cpu->reg.PC = branch_address;
}

void BEQ(CPU *cpu) {
    //Branch on EQual to zero
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->reg.P & ZERO) cpu->reg.PC = branch_address;
}

void BPL(CPU *cpu) {
    //Branch on PLus
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->reg.P & NEGATIVE)) cpu->reg.PC = branch_address;
}

void BMI(CPU *cpu) {
    //Branch on MInus
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->reg.P & NEGATIVE) cpu->reg.PC = branch_address;
}

void BVC(CPU *cpu) {
    //Branch on oVerflow Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->reg.P & OVERFLOW)) cpu->reg.PC = branch_address;
}

void BVS(CPU *cpu) {
    //Branch on oVerflow Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->reg.P & OVERFLOW) cpu->reg.PC = branch_address;
}

void CLC(CPU *cpu) {
    // CLear Carry
    cpu->reg.P &= ~CARRY;
}

void CLD(CPU *cpu) {
    // CLear Decimal
    cpu->reg.P &= ~DECIMAL;
}

void CLI(CPU *cpu) {
    // CLear Interrupt
    cpu->reg.P &= ~IRQ;
}

void CLV(CPU *cpu) {
    // CLear oVerflow
    cpu->reg.P &= ~OVERFLOW;
}

void DEC(CPU *cpu, uint8_t addressing_mode) {
    *(cpu->RAM + get_address(cpu, addressing_mode)) -= 1;
}

void DEX(CPU *cpu) {
    cpu->reg.X -= 1;
    set_flags(cpu, cpu->reg.X);
}

void DEY(CPU *cpu) {
    cpu->reg.Y -= 1;
    set_flags(cpu, cpu->reg.Y);
}

void EOR(CPU *cpu, uint8_t addressing_mode) {
    cpu->reg.A ^= get_operand(cpu, addressing_mode);
}

void INC(CPU *cpu, uint8_t addressing_mode) {
    *(cpu->RAM + get_address(cpu, addressing_mode)) += 1;
}

void INX(CPU *cpu) {
    cpu->reg.X += 1;
}

void INY(CPU *cpu) {
    cpu->reg.Y += 1;
}

void JMP(CPU *cpu, uint8_t addressing_mode) {
    cpu->reg.PC = get_address(cpu, addressing_mode);
}

void LDA(CPU *cpu, uint8_t addressing_mode) {
    //LoaD A
    cpu->reg.A = get_operand(cpu, addressing_mode);
    if (cpu->reg.A == 0) cpu->reg.P |= ZERO;
    if (cpu->reg.A & 0b10000000) cpu->reg.P |= NEGATIVE;
}

void LDX(CPU *cpu, uint8_t addressing_mode) {
    //LoaD X
    cpu->reg.X = get_operand(cpu, addressing_mode);
}

void LDY(CPU *cpu, uint8_t addressing_mode) {
    //LoaD Y
    cpu->reg.Y = get_operand(cpu, addressing_mode);
    if (cpu->reg.Y == 0) cpu->reg.P |= ZERO;
    if (cpu->reg.Y & 0b10000000) cpu->reg.P |= NEGATIVE;

}

void ORA(CPU *cpu, uint8_t addressing_mode) {
    //OR Accumulator
    cpu->reg.A &= get_operand(cpu, addressing_mode);
}

void PHA(CPU *cpu) {
    //PusH Accumulator
    *(cpu->RAM + cpu->reg.SP--) = cpu->reg.A;
}

void PLA(CPU *cpu) {
    //PuLl Accumulator
    cpu->reg.A = *(cpu->RAM + cpu->reg.SP++);
}

void PHP(CPU *cpu) {
    //PusH Processor status
    *(cpu->RAM + cpu->reg.SP--) = cpu->reg.P;
}

void PLP(CPU *cpu) {
    //PuLl Processor status
    cpu->reg.P = *(cpu->RAM + cpu->reg.SP++);
}

void SEC(CPU *cpu) {
    //SEt Carry
    cpu->reg.P |= CARRY;
}

void SED(CPU *cpu) {
    //SEt Decimal
    cpu->reg.P |= DECIMAL;
}

void SEI(CPU *cpu) {
    //SEt Interrupt
    cpu->reg.P |= IRQ;
}

void STA(CPU *cpu, uint8_t addressing_mode) {
    //Store A
    *(cpu->RAM + get_address(cpu, addressing_mode)) = cpu->reg.A;
}

void STX(CPU *cpu, uint8_t addressing_mode) {
    //Store X
    *(cpu->RAM + get_address(cpu, addressing_mode)) = cpu->reg.X;
}

void STY(CPU *cpu, uint8_t addressing_mode) {
    //Store Y
    *(cpu->RAM + get_address(cpu, addressing_mode)) = cpu->reg.Y;
}

void TAX(CPU *cpu) {
    //Transfer Accumulator to X
    cpu->reg.X = cpu->reg.A;
}

void TXA(CPU *cpu) {
    //Transfer X to Accumulator
    cpu->reg.A = cpu->reg.X;
}

void TAY(CPU *cpu) {
    //Transfer Accumulator to Y
    cpu->reg.Y = cpu->reg.A;
}

void TYA(CPU *cpu) {
    //Transfer Y to Accumulator
    cpu->reg.A = cpu->reg.Y;
}

void TSX(CPU *cpu) {
    //Transfer Stack pointer to X
    cpu->reg.X = cpu->reg.SP;
}

void TXS(CPU *cpu) {
    //Transfer X to Stack pointer
    cpu->reg.SP = cpu->reg.X;
}







