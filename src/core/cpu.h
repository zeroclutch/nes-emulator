#pragma once

#include <stdint.h>
#include <array>
#include <map>
#include <emscripten.h>

#include "memory.h"
#include "instructions.h"

#define VERBOSE 1
#define CONCAT(arg0, arg1) (((uint16_t) arg1) << 8) | arg0

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
#define FLAG_BREAK      0b00010000
#define FLAG_UNUSED     0b00100000
#define FLAG_OVERFLOW   0b01000000
#define FLAG_NEGATIVE   0b10000000

class CPU {
    public:
        CPU();
        ~CPU();

        void reset();
        
        // Registers
        struct registers registers;

        // Methods
        instruction_t fetch(uint8_t opcode);
        uint16_t decode(uint8_t arg0, uint8_t arg1, uint8_t mode);
        void exec(instruction_t *instr, uint8_t opcode, uint16_t arg);
        void load(uint8_t program[], size_t program_size);
        void load_and_run(uint8_t program[], size_t program_size);
        void run();
        void run(void (*callback)(void));

        // Flags
        void updateCarryFlag(uint8_t value, uint8_t a, uint8_t b);
        void updateZeroFlag(uint8_t value);
        void updateOverflowFlag(uint8_t value, uint8_t a, uint8_t b);
        void updateNegativeFlag(uint8_t value);

        void updateFlags(uint8_t value, uint8_t a, uint8_t b);
        
        // Memory
        uint8_t memoryRead(uint16_t address);
        uint16_t memoryReadu16(uint16_t address);
        void memoryWrite(uint16_t address, uint8_t value);
        void memoryWriteu16(uint16_t address, uint16_t value);
        void memoryLoad(uint8_t block[], size_t size);

        void pushStack(uint8_t value);
        uint8_t popStack();
        void pushStacku16(uint16_t value);
        uint16_t popStacku16();

        // Instructions
        void ADC(uint8_t mode, uint16_t arg);
        void AND(uint8_t mode, uint16_t arg);
        void ASL(uint8_t mode, uint16_t arg);
        void BCC(uint8_t mode, uint16_t arg);
        void BCS(uint8_t mode, uint16_t arg);
        void BEQ(uint8_t mode, uint16_t arg);
        void BIT(uint8_t mode, uint16_t arg);
        void BMI(uint8_t mode, uint16_t arg);
        void BNE(uint8_t mode, uint16_t arg);
        void BPL(uint8_t mode, uint16_t arg);
        void BRK(uint8_t mode, uint16_t arg);
        void BVC(uint8_t mode, uint16_t arg);
        void BVS(uint8_t mode, uint16_t arg);
        void CLC(uint8_t mode, uint16_t arg);
        void CLD(uint8_t mode, uint16_t arg);
        void CLI(uint8_t mode, uint16_t arg);
        void CLV(uint8_t mode, uint16_t arg);
        void CMP(uint8_t mode, uint16_t arg);
        void CPX(uint8_t mode, uint16_t arg);
        void CPY(uint8_t mode, uint16_t arg);
        void DEC(uint8_t mode, uint16_t arg);
        void DEX(uint8_t mode, uint16_t arg);
        void DEY(uint8_t mode, uint16_t arg);
        void EOR(uint8_t mode, uint16_t arg);
        void INC(uint8_t mode, uint16_t arg);
        void INX(uint8_t mode, uint16_t arg);
        void INY(uint8_t mode, uint16_t arg);
        void JMP(uint8_t mode, uint16_t arg);
        void JSR(uint8_t mode, uint16_t arg);
        void LDA(uint8_t mode, uint16_t arg);
        void LDX(uint8_t mode, uint16_t arg);
        void LDY(uint8_t mode, uint16_t arg);
        void LSR(uint8_t mode, uint16_t arg);
        void NOP(uint8_t mode, uint16_t arg);
        void ORA(uint8_t mode, uint16_t arg);
        void PHA(uint8_t mode, uint16_t arg);
        void PHP(uint8_t mode, uint16_t arg);
        void PLA(uint8_t mode, uint16_t arg);
        void PLP(uint8_t mode, uint16_t arg);
        void ROL(uint8_t mode, uint16_t arg);
        void ROR(uint8_t mode, uint16_t arg);
        void RTI(uint8_t mode, uint16_t arg);
        void RTS(uint8_t mode, uint16_t arg);
        void SBC(uint8_t mode, uint16_t arg);
        void SEC(uint8_t mode, uint16_t arg);
        void SED(uint8_t mode, uint16_t arg);
        void SEI(uint8_t mode, uint16_t arg);
        void STA(uint8_t mode, uint16_t arg);
        void STX(uint8_t mode, uint16_t arg);
        void STY(uint8_t mode, uint16_t arg);
        void TAX(uint8_t mode, uint16_t arg);
        void TAY(uint8_t mode, uint16_t arg);
        void TSX(uint8_t mode, uint16_t arg);
        void TXA(uint8_t mode, uint16_t arg);
        void TXS(uint8_t mode, uint16_t arg);
        void TYA(uint8_t mode, uint16_t arg);

};