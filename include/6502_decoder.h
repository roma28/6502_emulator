// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Created by Roman Ishchenko on 18.04.2022.
//

#ifndef INC_6502EMULATOR_6502_DECODER_H
#define INC_6502EMULATOR_6502_DECODER_H
#include <stdlib.h>
#include "6502_instructions.h"

uint16_t get_address(CPU *cpu, uint8_t addressing_mode);

uint8_t get_operand(CPU *cpu, uint8_t addressing_mode);

void decode(CPU *cpu, uint8_t opcode);

/**
 * Fetches the next instuction from RAM
 * @param cpu pointer to a CPU instance
 * @return instruction opcode
 */
uint8_t fetch(CPU *cpu);

#endif //INC_6502EMULATOR_6502_DECODER_H
