# 6502 Emulator

This is an emulator of 6502 CPU written in C99 as a study project.

## Implemented

* Simple `switch-case` emulation of legal opcodes
* Hard reset sequence
* All addressing modes
* Simple write-only terminal (using `ncurses` library)

## Not (yet) implemented

* Interrupts
* Reading from terminal
* Glitches
* Cycle counter

## Memory map

* Program memory (ROM) is located from `0x8000` to `0xFFFF`
* Terminal output is mapped to `0x2000` - `0x2780` (standard `80x24` window)

## References

* https://en.wikibooks.org/wiki/6502_Assembly
* W65C02S Datasheet