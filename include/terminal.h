//
// Created by Roman Ishchenko on 28.04.2022.
//

#ifndef INC_6502EMULATOR_TERMINAL_H
#define INC_6502EMULATOR_TERMINAL_H

#include <ncurses.h>
#include "../include/6502_basic_structures.h"

void update_terminal(CPU *cpu);

#define TERMINAL_OUTPUT 0x2000
#define TERMINAL_INPUT 0x27D0
#define TERMINAL_CONTROL 0x1FFF


#endif //INC_6502EMULATOR_TERMINAL_H
