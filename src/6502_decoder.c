// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//


#include <stdio.h>
#include "../include/6502_decoder.h"

uint16_t get_address(CPU *cpu, uint8_t addressing_mode) {
    // returns the address of the operand
    uint16_t addr;

    switch (addressing_mode) {
        case ABSOLUTE_INDIRECT: // address is stored in two following bytes in LE
            addr = *(cpu->RAM + cpu->reg.PC) | *(cpu->RAM + cpu->reg.PC + 1) << 8; // forming from two bytes
            cpu->reg.PC += 2;
            break;
        case ABSOLUTE_INDEXED_X: // address is stored in two following bytes in LE + shift in X
            addr = *(cpu->RAM + cpu->reg.PC) | *(cpu->RAM + cpu->reg.PC + 1) << 8;
            addr += cpu->reg.X;
            cpu->reg.PC += 2;
            break;
        case ABSOLUTE_INDEXED_Y: // address is stored in two following bytes in LE + shift in Y
            addr = *(cpu->RAM + cpu->reg.PC) | *(cpu->RAM + cpu->reg.PC + 1) << 8;
            addr += cpu->reg.Y;
            cpu->reg.PC += 2;
            break;
        case IMMEDIATE: // operand is the next byte
            addr = cpu->reg.PC;
            cpu->reg.PC++;
            break;
        case ZERO_PAGE:
            addr = cpu->reg.PC | (0x00 << 8);
            cpu->reg.PC++;
    }

    return addr;
}

uint8_t get_operand(CPU *cpu, uint8_t addressing_mode) {
    return *(cpu->RAM + get_address(cpu, addressing_mode));
}

void decode(CPU *cpu, uint8_t opcode) {
    switch (opcode) {
        case 0x69:
            ADC(cpu, IMMEDIATE);
            break;
        case 0x6d:
            ADC(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0x18:
            CLC(cpu);
            break;
        case 0xe8:
            INX(cpu);
            break;
        case 0xc8:
            INY(cpu);
            break;
        case 0xad:
            LDA(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0xbd:
            LDA(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0xb9:
            LDA(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0xa9:
            LDA(cpu, IMMEDIATE);
            break;
        case 0xa5:
            LDA(cpu, ZERO_PAGE);
            break;
        case 0xa1:
            LDA(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0xB5:
            LDA(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0xb1:
            LDA(cpu, ZERO_PAGE_INDEXED_Y_INDIRECT);
            break;
        case 0xa2:
            LDX(cpu, IMMEDIATE);
            break;
        case 0xae:
            LDX(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0xac:
            LDY(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0xa0:
            LDY(cpu, IMMEDIATE);
            break;
        case 0xea:
            break;
        case 0x09:
            ORA(cpu, IMMEDIATE);
            break;
        case 0x0d:
            ORA(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0x8d:
            STA(cpu, ABSOLUTE_INDIRECT);
            break;
        default:
            printf("Not implemented opcode %02X", opcode);
            break;
    }
}

uint8_t fetch(CPU *cpu) {
    cpu->reg.PC++;
    return *(cpu->RAM + cpu->reg.PC - 1);


}

