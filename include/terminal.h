//
// Created by Roman Ishchenko on 28.04.2022.
//

#ifndef INC_6502EMULATOR_TERMINAL_H
#define INC_6502EMULATOR_TERMINAL_H

#include <ncurses.h>
#include "../include/6502_basic_structures.h"

void update_terminal(CPU *cpu);

#endif //INC_6502EMULATOR_TERMINAL_H
