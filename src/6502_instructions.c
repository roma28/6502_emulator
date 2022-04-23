// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include <stdio.h>
#include "../include/6502_instructions.h"


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
    cpu->reg.PC++;
}

void CLC(CPU *cpu) {
    // CLear Carrry
    cpu->reg.P &= ~CARRY;
    cpu->reg.PC++;
}

void DEC(CPU *cpu) {
    cpu->reg.A -= 1;
    cpu->reg.PC++;
}

void DEX(CPU *cpu) {
    cpu->reg.X -= 1;
    cpu->reg.PC++;
}

void DEY(CPU *cpu) {
    cpu->reg.Y -= 1;
    cpu->reg.PC++;
}

void EOR(CPU *cpu, uint8_t addressing_mode) {
    cpu->reg.A ^= get_operand(cpu, addressing_mode);
}

void INX(CPU *cpu) {
    cpu->reg.X += 1;
    cpu->reg.PC++;
}

void INY(CPU *cpu) {
    cpu->reg.Y += 1;
    cpu->reg.PC++;
}

void LDA(CPU *cpu, uint8_t addressing_mode) {
    //LoaD A
    cpu->reg.A = get_operand(cpu, addressing_mode);
}

void LDX(CPU *cpu, uint8_t addressing_mode) {
    //LoaD X
    cpu->reg.X = get_operand(cpu, addressing_mode);
}

void LDY(CPU *cpu, uint8_t addressing_mode) {
    //LoaD Y
    cpu->reg.Y = get_operand(cpu, addressing_mode);
}

void ORA(CPU *cpu, uint8_t addressing_mode) {
    //OR Accumulator
    cpu->reg.A &= get_operand(cpu, addressing_mode);
    if (cpu->reg.A == 0) cpu->reg.P |= ZERO;
    if (cpu->reg.A >> 7 == 1) cpu->reg.P |= NEGATIVE;
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



