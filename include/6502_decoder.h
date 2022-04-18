//
// Created by Roman Ishchenko on 18.04.2022.
//

#ifndef INC_6502EMULATOR_6502_DECODER_H
#define INC_6502EMULATOR_6502_DECODER_H
#include <stdlib.h>
#include "6502_instructions.h"

uint16_t get_address(CPU *cpu, uint8_t addressing_mode);

uint8_t get_operand(CPU *cpu, uint8_t addressing_mode);

void decode(CPU *cpu, uint8_t instruction);

uint8_t fetch(CPU *cpu);

#endif //INC_6502EMULATOR_6502_DECODER_H
