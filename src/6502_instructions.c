// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include <stdio.h>
#include "../include/6502_instructions.h"

void ADC(CPU *cpu, uint8_t addressing_mode) {
    //ADd memory to accumulator with Carry
    uint16_t operand;
    
    switch (addressing_mode) {
        case IMMEDIATE: // the operand is the next byte
            cpu->reg.PC++;
            operand = *(cpu->RAM+cpu->reg.PC);
            cpu->reg.PC++;
    }
    uint16_t res = cpu->reg.A + operand;
    if (res & (1 << 8)) cpu->reg.P |= CARRY; // checking if overflow happened
    cpu->reg.A = res & 0xff; // stroring only lower byte
}

void AND(CPU *cpu) {
    cpu->reg.A &= *(cpu->RAM);
}

void ASL(CPU *cpu) {
    cpu->reg.A <<= 1;
}

void CLC(CPU *cpu) {
    cpu->reg.P &= ~CARRY;
}

void DEC(CPU *cpu) {
    cpu->reg.A -= 1;
}

void DEX(CPU *cpu) {
    cpu->reg.X -= 1;
}

void DEY(CPU *cpu) {
    cpu->reg.Y -= 1;
}

void LDA(CPU *cpu, uint8_t addressing_mode) {
    //LoaD A
    switch (addressing_mode) {
        case IMMEDIATE: // operand is the next byte
            cpu->reg.PC++;
            cpu->reg.A = *(cpu->RAM + cpu->reg.PC);
            cpu->reg.PC++;
            break;
    }
}

void STA(CPU *cpu, uint8_t addressing_mode) {
    //Store A
    switch (addressing_mode) {
        case ABSOLUTE_INDIRECT: // address is two next bytes in LE
            cpu->reg.PC++;
            uint16_t addr = *(cpu->RAM + cpu->reg.PC) | *(cpu->RAM + cpu->reg.PC + 1) << 8; // forming memory address
            *(cpu->RAM + addr) = cpu->reg.A;
            cpu->reg.PC += 2;
            break;
    }
}
