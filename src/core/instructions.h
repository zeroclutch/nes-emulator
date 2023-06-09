#pragma once
#include <map>

enum INSTRUCTIONS_6502 {
   INSTR_ADC,
   INSTR_AND,
   INSTR_ASL,
   INSTR_BCC,
   INSTR_BCS,
   INSTR_BEQ,
   INSTR_BIT,
   INSTR_BMI,
   INSTR_BNE,
   INSTR_BPL,
   INSTR_BRK,
   INSTR_BVC,
   INSTR_BVS,
   INSTR_CLC,
   INSTR_CLD,
   INSTR_CLI,
   INSTR_CLV,
   INSTR_CMP,
   INSTR_CPX,
   INSTR_CPY,
   INSTR_DEC,
   INSTR_DEX,
   INSTR_DEY,
   INSTR_EOR,
   INSTR_INC,
   INSTR_INX,
   INSTR_INY,
   INSTR_JMP,
   INSTR_JSR,
   INSTR_LDA,
   INSTR_LDX,
   INSTR_LDY,
   INSTR_LSR,
   INSTR_NOP,
   INSTR_ORA,
   INSTR_PHA,
   INSTR_PHP,
   INSTR_PLA,
   INSTR_PLP,
   INSTR_ROL,
   INSTR_ROR,
   INSTR_RTI,
   INSTR_RTS,
   INSTR_SBC,
   INSTR_SEC,
   INSTR_SED,
   INSTR_SEI,
   INSTR_STA,
   INSTR_STX,
   INSTR_STY,
   INSTR_TAX,
   INSTR_TAY,
   INSTR_TSX,
   INSTR_TXA,
   INSTR_TXS,
   INSTR_TYA,
};

enum AddressingMode {
   Immediate,
   ZeroPage,
   ZeroPage_X,
   ZeroPage_Y,
   Absolute,
   Absolute_X,
   Absolute_Y,
   Indirect,
   Indirect_X,
   Indirect_Y,
   Relative,
   NoneAddressing,
};

typedef struct instruction {
    uint8_t bytes;
    uint8_t cycles;
    uint8_t name;
    uint8_t mode;
} instruction_t;

extern std::map<uint8_t, instruction_t> instructionSet;