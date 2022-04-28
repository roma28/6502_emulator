//
// Created by Roman Ishchenko on 28.04.2022.
//

#include "../include/terminal.h"
#include <string.h>

void update_terminal(CPU *cpu) {
    clear();
    for (size_t i = 0; i < 24; ++i) {
        for (size_t j = 0; j < 80; ++j) {
            char ch = (char) cpu->MEM[TERMINAL_OUTPUT + 24 * i + j];
            if (ch) {
                mvaddch(i, j, ch);
            } else {
                break;
            }
        }
    }
    refresh();
    getstr((char *) &cpu->MEM[TERMINAL_INPUT]);
}
