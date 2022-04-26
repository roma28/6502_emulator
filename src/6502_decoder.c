// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//


#include <stdio.h>
#include "../include/6502_decoder.h"

/**
 * Fetches the next instruction from MEM
 * @param cpu pointer to a CPU instance
 * @return instruction opcode
 */
uint8_t fetch(CPU *cpu) {
    cpu->reg.PC++;
    return *(cpu->MEM + cpu->reg.PC - 1);
}

/**
 * Loads the operand from the MEM
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 * @return Operand value
 */
uint8_t get_operand(CPU *cpu, uint8_t addressing_mode) {
    return cpu->MEM[get_address(cpu, addressing_mode)];
}

/**
 * Gives the address in the MEM of the instruction operand
 * @param cpu pointer to a CPU instance
 * @param addressing_mode addressing mode, specifies how the address of the operand is stored
 * @return Operand address in MEM
 */
uint16_t get_address(CPU *cpu, uint8_t addressing_mode) {

    uint16_t addr;
    uint16_t tmp_addr; // for indirect addressing

    switch (addressing_mode) {
        case ABSOLUTE: // address is stored in two following bytes in LE
            addr = cpu->MEM[cpu->reg.PC] | (cpu->MEM[cpu->reg.PC + 1] << 8);
            cpu->reg.PC += 2;
            break;
        case ABSOLUTE_INDEXED_X: // address is stored in two following bytes in LE + shift in X
            addr = cpu->MEM[cpu->reg.PC] | (cpu->MEM[cpu->reg.PC + 1] << 8);
            addr += cpu->reg.X;
            cpu->reg.PC += 2;
            break;
        case ABSOLUTE_INDEXED_Y: // address is stored in two following bytes in LE + shift in Y
            addr = cpu->MEM[cpu->reg.PC] | (cpu->MEM[cpu->reg.PC + 1] << 8);
            addr += cpu->reg.Y;
            cpu->reg.PC += 2;
            break;
        case IMMEDIATE: // operand is the next byte
            addr = cpu->reg.PC;
            cpu->reg.PC++;
            break;
        case ZERO_PAGE: //the following byte is lower byte of the address, the upper byte is always 0x00
            addr = cpu->reg.PC | (0x00 << 8);
            cpu->reg.PC++;
            break;
        case RELATIVE:
            addr = cpu->reg.PC + (int8_t) cpu->MEM[cpu->reg.PC] + 1;
            cpu->reg.PC++;
            break;
        case ABSOLUTE_INDIRECT:
            tmp_addr = cpu->MEM[cpu->reg.PC] |
                       (cpu->MEM[cpu->reg.PC + 1] << 8); // forming address of the operand address
            cpu->reg.PC += 2;
            addr = cpu->MEM[tmp_addr] | (cpu->MEM[tmp_addr + 1] << 8); // reading address from memory in LE
            break;
        case ZERO_PAGE_INDEXED_X: //the following byte is lower byte of the address, the upper byte is always 0x00 + shift in X
            addr = cpu->reg.PC | (0x00 << 8);
            addr += cpu->reg.X;
            cpu->reg.PC++;
            break;
        case ZERO_PAGE_INDEXED_Y: //the following byte is lower byte of the address, the upper byte is always 0x00 + shift in Y
            addr = cpu->reg.PC | (0x00 << 8);
            addr += cpu->reg.Y;
            cpu->reg.PC++;
            break;
        case ZERO_PAGE_INDEXED_X_INDIRECT:
            tmp_addr = (cpu->MEM[cpu->reg.PC] | (0x00 << 8)) + cpu->reg.X; // forming address of the address
            cpu->reg.PC++;
            addr = cpu->MEM[tmp_addr] | (cpu->MEM[tmp_addr + 1] << 8); // reading address from memory in LE
            break;
        case ZERO_PAGE_INDIRECT_INDEXED_Y:
            tmp_addr = (cpu->MEM[cpu->reg.PC] | (0x00 << 8)); // forming address of the address
            cpu->reg.PC++;
            addr = cpu->MEM[tmp_addr] | (cpu->MEM[tmp_addr + 1] << 8) +
                                        cpu->reg.Y; // reading address from memory in LE
            break;

        default:
            printf("Addressing mode is unknown");
            addr = 0;
    }

    return addr;
}

void decode(CPU *cpu, uint8_t opcode) {
    switch (opcode) {
        case 0x6d:
            ADC(cpu, ABSOLUTE);
            break;
        case 0x7d:
            ADC(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0x79:
            ADC(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0x69:
            ADC(cpu, IMMEDIATE);
            break;
        case 0x65:
            ADC(cpu, ZERO_PAGE);
            break;
        case 0x61:
            ADC(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0x75:
            ADC(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0x71:
            ADC(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;

        case 0x2d:
            AND(cpu, ABSOLUTE);
            break;
        case 0x3d:
            AND(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0x39:
            AND(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0x29:
            AND(cpu, IMMEDIATE);
            break;
        case 0x25:
            AND(cpu, ZERO_PAGE);
            break;
        case 0x21:
            AND(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0x35:
            AND(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0x31:
            AND(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;

            // Branching
        case 0x90:
            BCC(cpu);
            break;
        case 0xb0:
            BCS(cpu);
            break;
        case 0xd0:
            BNE(cpu);
            break;
        case 0xf0:
            BEQ(cpu);
            break;
        case 0x10:
            BPL(cpu);
            break;
        case 0x30:
            BMI(cpu);
            break;
        case 0x50:
            BVC(cpu);
            break;
        case 0x70:
            BVS(cpu);
            break;

            // Clearing/setting flags
        case 0x18:
            CLC(cpu);
            break;
        case 0x38:
            SEC(cpu);
            break;
        case 0xd8:
            CLD(cpu);
            break;
        case 0xf8:
            SED(cpu);
            break;
        case 0x58:
            CLI(cpu);
            break;
        case 0x78:
            SEI(cpu);
            break;
        case 0xb8:
            CLV(cpu);
            break;

            // Increments/decrements
        case 0xce:
            DEC(cpu, ABSOLUTE);
            break;
        case 0xde:
            DEC(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0xc6:
            DEC(cpu, ZERO_PAGE);
            break;
        case 0xd6:
            DEC(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0xca:
            DEX(cpu);
            break;
        case 0x88:
            DEY(cpu);
            break;
        case 0xee:
            INC(cpu, ABSOLUTE);
            break;
        case 0xfe:
            INC(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0xe6:
            INC(cpu, ZERO_PAGE);
            break;
        case 0xf6:
            INC(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0xe8:
            INX(cpu);
            break;
        case 0xc8:
            INY(cpu);
            break;

        case 0x4d:
            EOR(cpu, ABSOLUTE);
            break;
        case 0x5d:
            EOR(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0x59:
            EOR(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0x49:
            EOR(cpu, IMMEDIATE);
            break;
        case 0x45:
            EOR(cpu, ZERO_PAGE);
            break;
        case 0x41:
            EOR(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0x55:
            EOR(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0x51:
            EOR(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;

            // Jumping
        case 0x4c:
            JMP(cpu, ABSOLUTE);
            break;
        case 0x6c:
            JMP(cpu, ABSOLUTE_INDIRECT);
            break;
        case 0x20:
            JSR(cpu);
            break;

            // Loading registers
        case 0xad:
            LDA(cpu, ABSOLUTE);
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
            LDA(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;
        case 0xae:
            LDX(cpu, ABSOLUTE);
            break;
        case 0xbe:
            LDX(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0xa2:
            LDX(cpu, IMMEDIATE);
            break;
        case 0xa6:
            LDX(cpu, ZERO_PAGE);
            break;
        case 0xb6:
            LDX(cpu, ZERO_PAGE_INDEXED_Y);
            break;
        case 0xac:
            LDY(cpu, ABSOLUTE);
            break;
        case 0xbc:
            LDY(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0xa0:
            LDY(cpu, IMMEDIATE);
            break;
        case 0xa4:
            LDY(cpu, ZERO_PAGE);
            break;
        case 0xb4:
            LDY(cpu, ZERO_PAGE_INDEXED_X);
            break;

        case 0xea: //nop
            break;

        case 0x0d:
            ORA(cpu, ABSOLUTE);
            break;
        case 0x1d:
            ORA(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0x19:
            ORA(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0x09:
            ORA(cpu, IMMEDIATE);
            break;
        case 0x05:
            ORA(cpu, ZERO_PAGE);
            break;
        case 0x01:
            ORA(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0x15:
            ORA(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0x11:
            ORA(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;

            // Stack
        case 0x48:
            PHA(cpu);
            break;
        case 0x68:
            PLA(cpu);
            break;
        case 0x08:
            PHP(cpu);
            break;
        case 0x28:
            PLP(cpu);
            break;

        case 0x60:
            RTS(cpu);
            break;

            // Storing
        case 0x8d:
            STA(cpu, ABSOLUTE);
            break;
        case 0x9d:
            STA(cpu, ABSOLUTE_INDEXED_X);
            break;
        case 0x99:
            STA(cpu, ABSOLUTE_INDEXED_Y);
            break;
        case 0x85:
            STA(cpu, ZERO_PAGE);
            break;
        case 0x81:
            STA(cpu, ZERO_PAGE_INDEXED_X_INDIRECT);
            break;
        case 0x95:
            STA(cpu, ZERO_PAGE_INDEXED_X);
            break;
        case 0x91:
            STA(cpu, ZERO_PAGE_INDIRECT_INDEXED_Y);
            break;
        case 0x8e:
            STX(cpu, ABSOLUTE);
            break;
        case 0x86:
            STX(cpu, ZERO_PAGE);
            break;
        case 0x96:
            STX(cpu, ZERO_PAGE_INDEXED_Y);
            break;
        case 0x8c:
            STY(cpu, ABSOLUTE);
            break;
        case 0x84:
            STY(cpu, ZERO_PAGE);
            break;
        case 0x94:
            STY(cpu, ZERO_PAGE_INDEXED_X);
            break;

            // Transferring
        case 0xaa:
            TAX(cpu);
            break;
        case 0x8a:
            TXA(cpu);
            break;
        case 0xa8:
            TAY(cpu);
            break;
        case 0x98:
            TYA(cpu);
            break;
        case 0xba:
            TSX(cpu);
            break;
        case 0x9a:
            TXS(cpu);
            break;

        default:
            printf("Not implemented opcode %02X at %04X\n", opcode, cpu->reg.PC - 1);
            break;
    }
}


