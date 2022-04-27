// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#include <stdio.h>
#include "../include/6502_instructions.h"

void set_zero_negative_flags(CPU *cpu, uint8_t n) {
    if (n == 0) cpu->registers.P |= ZERO;
    if (n & 0b10000000) cpu->registers.P |= NEGATIVE;
}

void set_cmp_flags(CPU *cpu, a, b) {
    if (a == b) {
        cpu->registers.P |= (CARRY | ZERO);
        cpu->registers.P &= ~NEGATIVE;
    }
    if (a < b) {
        cpu->registers.P |= NEGATIVE;
        cpu->registers.P &= ~(CARRY | ZERO);
    }
    if (a > b) {
        cpu->registers.P |= CARRY;
        cpu->registers.P &= ~(NEGATIVE | ZERO);
    }
}

void ADC(CPU *cpu, uint8_t addressing_mode) {
    //ADd memory to accumulator with Carry
    uint8_t operand = get_operand(cpu, addressing_mode);

    uint16_t res = cpu->registers.A + operand;
    uint8_t res_lower = res & 0xff;
    res += cpu->registers.P & CARRY; // checking for carry flag

    if (res > 0xff) cpu->registers.P |= OVERFLOW;

    cpu->registers.A = res_lower;
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void AND(CPU *cpu, uint8_t addressing_mode) {
    //Accumulator aND
    cpu->registers.A &= get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void ASL(CPU *cpu) {
    //Accumulator Shift Left
    cpu->registers.A <<= 1;
}

void BCC(CPU *cpu) {
    //Branch on Carry Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->registers.P & CARRY)) cpu->registers.PC = branch_address;
}

void BCS(CPU *cpu) {
    //Branch on Carry Set
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->registers.P & CARRY) cpu->registers.PC = branch_address;
}

void BNE(CPU *cpu) {
    //Branch on Non-Zero
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->registers.P & ZERO)) cpu->registers.PC = branch_address;
}

void BEQ(CPU *cpu) {
    //Branch on EQual to zero
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->registers.P & ZERO) { cpu->registers.PC = branch_address; }
}

void BPL(CPU *cpu) {
    //Branch on PLus
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->registers.P & NEGATIVE)) cpu->registers.PC = branch_address;
}

void BMI(CPU *cpu) {
    //Branch on MInus
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->registers.P & NEGATIVE) cpu->registers.PC = branch_address;
}

void BVC(CPU *cpu) {
    //Branch on oVerflow Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (!(cpu->registers.P & OVERFLOW)) cpu->registers.PC = branch_address;
}

void BVS(CPU *cpu) {
    //Branch on oVerflow Clear
    uint16_t branch_address = get_address(cpu, RELATIVE);
    if (cpu->registers.P & OVERFLOW) cpu->registers.PC = branch_address;
}

void CLC(CPU *cpu) {
    // CLear Carry
    cpu->registers.P &= ~CARRY;
}

void CLD(CPU *cpu) {
    // CLear Decimal
    cpu->registers.P &= ~DECIMAL;
}

void CLI(CPU *cpu) {
    // CLear Interrupt
    cpu->registers.P &= ~IRQ;
}

void CLV(CPU *cpu) {
    // CLear oVerflow
    cpu->registers.P &= ~OVERFLOW;
}

void CMP(CPU *cpu, uint8_t addressing_mode) {
    uint8_t operand = get_operand(cpu, addressing_mode);
    set_cmp_flags(cpu, cpu->registers.A, operand);
}

void CPX(CPU *cpu, uint8_t addressing_mode) {
    uint8_t operand = get_operand(cpu, addressing_mode);
    set_cmp_flags(cpu, cpu->registers.X, operand);
}

void CPY(CPU *cpu, uint8_t addressing_mode) {
    uint8_t operand = get_operand(cpu, addressing_mode);
    set_cmp_flags(cpu, cpu->registers.Y, operand);
}


void DEC(CPU *cpu, uint8_t addressing_mode) {
    cpu->MEM[get_address(cpu, addressing_mode)] -= 1;
}

void DEX(CPU *cpu) {
    if (cpu->registers.X == 0) {
        cpu->registers.P |= OVERFLOW;
        cpu->registers.X = 0xff;
    } else cpu->registers.X -= 1;

    set_zero_negative_flags(cpu, cpu->registers.X);

}

void DEY(CPU *cpu) {
    if (cpu->registers.Y == 0) {
        cpu->registers.P |= OVERFLOW;
        cpu->registers.Y = 0xff;
    } else cpu->registers.Y -= 1;

    set_zero_negative_flags(cpu, cpu->registers.Y);
}

void EOR(CPU *cpu, uint8_t addressing_mode) {
    cpu->registers.A ^= get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void INC(CPU *cpu, uint8_t addressing_mode) {
    uint16_t addr = get_address(cpu, addressing_mode);
    if (cpu->MEM[addr] == 0xff) {
        cpu->registers.P |= OVERFLOW;
        cpu->MEM[addr] = 0;
    } else cpu->MEM[addr] += 1;

    set_zero_negative_flags(cpu, cpu->MEM[addr]);

}

void INX(CPU *cpu) {
    if (cpu->registers.X == 0xff) {
        cpu->registers.P |= OVERFLOW;
        cpu->registers.X = 0;
    } else cpu->registers.X += 1;

    set_zero_negative_flags(cpu, cpu->registers.X);
}

void INY(CPU *cpu) {
    if (cpu->registers.Y == 0xff) {
        cpu->registers.P |= OVERFLOW;
        cpu->registers.Y = 0;
    } else cpu->registers.Y += 1;

    set_zero_negative_flags(cpu, cpu->registers.Y);
}

void JMP(CPU *cpu, uint8_t addressing_mode) {
    cpu->registers.PC = get_address(cpu, addressing_mode);
}

void JSR(CPU *cpu) {
    //Jump to SubRoutine
    uint16_t jump_address = get_address(cpu, ABSOLUTE);
    uint16_t return_address = cpu->registers.PC - 1;
    cpu->MEM[cpu->registers.SP--] = (uint8_t) (return_address >> 8); // pushing upper byte
    cpu->MEM[cpu->registers.SP--] = (uint8_t) (return_address & 0xff); // pushing lowe byte
    cpu->registers.PC = jump_address;
}

void LDA(CPU *cpu, uint8_t addressing_mode) {
    //LoaD A
    cpu->registers.A = get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void LDX(CPU *cpu, uint8_t addressing_mode) {
    //LoaD X
    cpu->registers.X = get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.X);
}

void LDY(CPU *cpu, uint8_t addressing_mode) {
    //LoaD Y
    cpu->registers.Y = get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.Y);
}

void ORA(CPU *cpu, uint8_t addressing_mode) {
    //OR Accumulator
    cpu->registers.A |= get_operand(cpu, addressing_mode);
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void PHA(CPU *cpu) {
    //PusH Accumulator
    cpu->MEM[cpu->registers.SP--] = cpu->registers.A;
}

void PLA(CPU *cpu) {
    //PuLl Accumulator
    cpu->registers.A = cpu->MEM[cpu->registers.SP++];
}

void PHP(CPU *cpu) {
    //PusH Processor status
    cpu->MEM[cpu->registers.SP--] = cpu->registers.P;
}

void PLP(CPU *cpu) {
    //PuLl Processor status
    cpu->registers.P = cpu->MEM[cpu->registers.SP++];
}

void RTS(CPU *cpu) {
    //ReTurn from Subroutine
    uint8_t lower = cpu->MEM[cpu->registers.SP++]; // popping lower byte
    uint8_t upper = cpu->MEM[cpu->registers.SP++]; // popping upper byte
    uint16_t return_address = lower | (upper << 8);
    cpu->registers.PC = return_address + 1;
}

void SEC(CPU *cpu) {
    //SEt Carry
    cpu->registers.P |= CARRY;
}

void SED(CPU *cpu) {
    //SEt Decimal
    cpu->registers.P |= DECIMAL;
}

void SEI(CPU *cpu) {
    //SEt Interrupt
    cpu->registers.P |= IRQ;
}

void STA(CPU *cpu, uint8_t addressing_mode) {
    //Store A
    cpu->MEM[get_address(cpu, addressing_mode)] = cpu->registers.A;
}

void STX(CPU *cpu, uint8_t addressing_mode) {
    //Store X
    cpu->MEM[get_address(cpu, addressing_mode)] = cpu->registers.X;
}

void STY(CPU *cpu, uint8_t addressing_mode) {
    //Store Y
    cpu->MEM[get_address(cpu, addressing_mode)] = cpu->registers.Y;
}

void TAX(CPU *cpu) {
    //Transfer Accumulator to X
    cpu->registers.X = cpu->registers.A;
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void TXA(CPU *cpu) {
    //Transfer X to Accumulator
    cpu->registers.A = cpu->registers.X;
    set_zero_negative_flags(cpu, cpu->registers.X);
}

void TAY(CPU *cpu) {
    //Transfer Accumulator to Y
    cpu->registers.Y = cpu->registers.A;
    set_zero_negative_flags(cpu, cpu->registers.A);
}

void TYA(CPU *cpu) {
    //Transfer Y to Accumulator
    cpu->registers.A = cpu->registers.Y;
    set_zero_negative_flags(cpu, cpu->registers.Y);
}

void TSX(CPU *cpu) {
    //Transfer Stack pointer to X
    cpu->registers.X = cpu->registers.SP;
    set_zero_negative_flags(cpu, cpu->registers.SP);
}

void TXS(CPU *cpu) {
    //Transfer X to Stack pointer
    cpu->registers.SP = cpu->registers.X;
    set_zero_negative_flags(cpu, cpu->registers.X);
}







