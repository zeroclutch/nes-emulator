#pragma once

#include <stdint.h>
#include <array>
#include <map>
#include <emscripten.h>

#include "./instructions.h"

// Registers
struct registers {
    uint16_t PC; // Program Counter
    uint8_t  SP; // Stack Pointer
    uint8_t  A;  // Accumulator
    uint8_t  X;  // X Register
    uint8_t  Y;  // Y Register
    uint8_t  P;  // Processor Status
};

// Flags
#define FLAG_CARRY      0b00000001
#define FLAG_ZERO       0b00000010
#define FLAG_INTERRUPT  0b00000100
#define FLAG_DECIMAL    0b00001000
#define FLAG_B          0b00010000
#define FLAG_UNUSED     0b00100000
#define FLAG_OVERFLOW   0b01000000
#define FLAG_NEGATIVE   0b10000000

class CPU;
typedef void (CPU::*instr_handler_t)(uint8_t, uint16_t);

class CPU {
    public:
        CPU();
        ~CPU();

        void reset();
        
        // Registers
        struct registers registers;

        // Memory
        uint8_t memory[0xFF];
        uint8_t memoryRead(uint16_t address);
        void memoryWrite(uint16_t address, uint8_t value);
        void memoryLoad(uint8_t program[]);
        void load(uint8_t program[]);
        uint16_t memoryReadu16(uint16_t address);

        // Methods
        instruction_t fetch(uint8_t opcode);
        uint16_t decode(uint8_t arg0, uint8_t arg1, uint8_t mode);
        void exec(uint8_t program[]);

        // Instructions
        void LDA(uint8_t mode, uint16_t arg);
        void LDX(uint8_t mode, uint16_t arg);
        void LDY(uint8_t mode, uint16_t arg);

        void INX(uint8_t mode, uint16_t arg);
        void INY(uint8_t mode, uint16_t arg);

        void TAX(uint8_t mode, uint16_t arg);

        // Flags
        void updateZeroFlag(uint8_t value);
        void updateNegativeFlag(uint8_t value);
};