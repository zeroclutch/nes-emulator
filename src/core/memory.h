#pragma once

#include <stdint.h>

#define MEM_ZERO_PAGE_START     0x0000
#define MEM_ZERO_PAGE_END       0x00FF
#define MEM_SYSTEM_STACK_START  0x0100
#define MEM_SYSTEM_STACK_END    0x01FF
#define MEM_PROGRAM_START       0x8000

#define MEM_INTERRUPT_HANDLER 0xFFFA
#define MEM_RESET_LOCATION    0xFFFC
#define MEM_BRK_HANDLER       0xFFFE
#define MEM_IRQ_HANDLER       0xFFFF

const uint16_t MAX_SAFE_PROGRAM_SIZE = MEM_INTERRUPT_HANDLER - MEM_PROGRAM_START;

// Ensure memory block is allocated on the heap
extern uint8_t memory[0xFFFF];