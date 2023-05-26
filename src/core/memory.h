#pragma once

#include <stdint.h>

// #define MEM_ZERO_PAGE_START   (uint16_t) 0x0000
// #define MEM_ZERO_PAGE_END     (uint16_t) 0x00FF
// #define MEM_SYSTEM_STACK_START(uint16_t) 0x0100
// #define MEM_SYSTEM_STACK_END  (uint16_t) 0x01FF
// #define MEM_PROGRAM_START     (uint16_t) 0x8000
// #define MEM_INTERRUPT_HANDLER (uint16_t) 0xFFFA
// #define MEM_RESET_LOCATION    (uint16_t) 0xFFFC
// #define MEM_BRK_HANDLER       (uint16_t) 0xFFFE
// #define MEM_IRQ_HANDLER       (uint16_t) 0xFFFF

const uint16_t MEM_ZERO_PAGE_START    = 0x0000;
const uint16_t MEM_ZERO_PAGE_END      = 0x00FF;
const uint16_t MEM_SYSTEM_STACK_START = 0x0100;
const uint16_t MEM_SYSTEM_STACK_END   = 0x01FF;
const uint16_t MEM_PROGRAM_START      = 0x8000;
const uint16_t MEM_INTERRUPT_HANDLER  = 0xFFFA;
const uint16_t MEM_RESET_LOCATION     = 0xFFFC;
const uint16_t MEM_BRK_HANDLER        = 0xFFFE;
const uint16_t MEM_IRQ_HANDLER        = 0xFFFF;
 
const uint16_t MAX_SAFE_PROGRAM_SIZE = MEM_INTERRUPT_HANDLER - MEM_PROGRAM_START;

// Ensure memory block is allocated on the heap
extern uint8_t memory[0xFFFF];