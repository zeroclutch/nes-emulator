#include "instructions.h"

std::map<uint8_t, instruction_t> instructionSet = {
   { 0x69, { 2, 2, INSTR_ADC, Immediate } },
   { 0x65, { 2, 3, INSTR_ADC, ZeroPage } },
   { 0x75, { 2, 4, INSTR_ADC, ZeroPage_X } },
   { 0x6D, { 3, 4, INSTR_ADC, Absolute } },
   { 0x7D, { 3, 4 /*+1 if page crossed*/, INSTR_ADC, Absolute_X } },
   { 0x79, { 3, 4 /*+1 if page crossed*/, INSTR_ADC, Absolute_Y } },
   { 0x61, { 2, 6, INSTR_ADC, Indirect_X } },
   { 0x71, { 2, 5 /*+1 if page crossed*/, INSTR_ADC, Indirect_Y } },

   { 0x29, { 2, 2, INSTR_AND, Immediate } },
   { 0x25, { 2, 3, INSTR_AND, ZeroPage } },
   { 0x35, { 2, 4, INSTR_AND, ZeroPage_X } },
   { 0x2D, { 3, 4, INSTR_AND, Absolute } },
   { 0x3D, { 3, 4 /*+1 if page crossed*/, INSTR_AND, Absolute_X } },
   { 0x39, { 3, 4 /*+1 if page crossed*/, INSTR_AND, Absolute_Y } },
   { 0x21, { 2, 6, INSTR_AND, Indirect_X } },
   { 0x31, { 2, 5 /*+1 if page crossed*/, INSTR_AND, Indirect_Y } },

   { 0x0A, { 1, 2, INSTR_ASL, NoneAddressing } },
   { 0x06, { 2, 5, INSTR_ASL, ZeroPage } },
   { 0x16, { 2, 6, INSTR_ASL, ZeroPage_X } },
   { 0x0E, { 3, 6, INSTR_ASL, Absolute } },
   { 0x1E, { 3, 7, INSTR_ASL, Absolute_X } },

   { 0x90, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BCC, Relative } },

   { 0xB0, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BCS, Relative } },

   { 0xF0, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BEQ, Relative } },

   { 0x24, { 2, 3, INSTR_BIT, ZeroPage } },
   { 0x2C, { 3, 4, INSTR_BIT, Absolute } },

   { 0x30, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BMI, Relative } },

   { 0xD0, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BNE, Relative } },

   { 0x10, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BPL, Relative } },

   { 0x00, { 1, 7, INSTR_BRK, NoneAddressing } },

   { 0x50, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BVC, Relative } },

   { 0x70, { 2, 2 /*+1 if branch succeeds+2 if to a new page*/, INSTR_BVS, Relative } },

   { 0x18, { 1, 2, INSTR_CLC, NoneAddressing } },

   { 0xD8, { 1, 2, INSTR_CLD, NoneAddressing } },

   { 0x58, { 1, 2, INSTR_CLI, NoneAddressing } },

   { 0xB8, { 1, 2, INSTR_CLV, NoneAddressing } },

   { 0xC9, { 2, 2, INSTR_CMP, Immediate } },
   { 0xC5, { 2, 3, INSTR_CMP, ZeroPage } },
   { 0xD5, { 2, 4, INSTR_CMP, ZeroPage_X } },
   { 0xCD, { 3, 4, INSTR_CMP, Absolute } },
   { 0xDD, { 3, 4 /*+1 if page crossed*/, INSTR_CMP, Absolute_X } },
   { 0xD9, { 3, 4 /*+1 if page crossed*/, INSTR_CMP, Absolute_Y } },
   { 0xC1, { 2, 6, INSTR_CMP, Indirect_X } },
   { 0xD1, { 2, 5 /*+1 if page crossed*/, INSTR_CMP, Indirect_Y } },

   { 0xE0, { 2, 2, INSTR_CPX, Immediate } },
   { 0xE4, { 2, 3, INSTR_CPX, ZeroPage } },
   { 0xEC, { 3, 4, INSTR_CPX, Absolute } },

   { 0xC0, { 2, 2, INSTR_CPY, Immediate } },
   { 0xC4, { 2, 3, INSTR_CPY, ZeroPage } },
   { 0xCC, { 3, 4, INSTR_CPY, Absolute } },

   { 0xC6, { 2, 5, INSTR_DEC, ZeroPage } },
   { 0xD6, { 2, 6, INSTR_DEC, ZeroPage_X } },
   { 0xCE, { 3, 6, INSTR_DEC, Absolute } },
   { 0xDE, { 3, 7, INSTR_DEC, Absolute_X } },

   { 0xCA, { 1, 2, INSTR_DEX, NoneAddressing } },

   { 0x88, { 1, 2, INSTR_DEY, NoneAddressing } },

   { 0x49, { 2, 2, INSTR_EOR, Immediate } },
   { 0x45, { 2, 3, INSTR_EOR, ZeroPage } },
   { 0x55, { 2, 4, INSTR_EOR, ZeroPage_X } },
   { 0x4D, { 3, 4, INSTR_EOR, Absolute } },
   { 0x5D, { 3, 4 /*+1 if page crossed*/, INSTR_EOR, Absolute_X } },
   { 0x59, { 3, 4 /*+1 if page crossed*/, INSTR_EOR, Absolute_Y } },
   { 0x41, { 2, 6, INSTR_EOR, Indirect_X } },
   { 0x51, { 2, 5 /*+1 if page crossed*/, INSTR_EOR, Indirect_Y } },

   { 0xE6, { 2, 5, INSTR_INC, ZeroPage } },
   { 0xF6, { 2, 6, INSTR_INC, ZeroPage_X } },
   { 0xEE, { 3, 6, INSTR_INC, Absolute } },
   { 0xFE, { 3, 7, INSTR_INC, Absolute_X } },

   { 0xE8, { 1, 2, INSTR_INX, NoneAddressing } },

   { 0xC8, { 1, 2, INSTR_INY, NoneAddressing } },

   { 0x4C, { 3, 3, INSTR_JMP, Absolute } },
   { 0x6C, { 3, 5, INSTR_JMP, Indirect } },

   { 0x20, { 3, 6, INSTR_JSR, Absolute } },

   { 0xA9, { 2, 2, INSTR_LDA, Immediate } },
   { 0xA5, { 2, 3, INSTR_LDA, ZeroPage } },
   { 0xB5, { 2, 4, INSTR_LDA, ZeroPage_X } },
   { 0xAD, { 3, 4, INSTR_LDA, Absolute } },
   { 0xBD, { 3, 4 /*+1 if page crossed*/, INSTR_LDA, Absolute_X } },
   { 0xB9, { 3, 4 /*+1 if page crossed*/, INSTR_LDA, Absolute_Y } },
   { 0xA1, { 2, 6, INSTR_LDA, Indirect_X } },
   { 0xB1, { 2, 5 /*+1 if page crossed*/, INSTR_LDA, Indirect_Y } },

   { 0xA2, { 2, 2, INSTR_LDX, Immediate } },
   { 0xA6, { 2, 3, INSTR_LDX, ZeroPage } },
   { 0xB6, { 2, 4, INSTR_LDX, ZeroPage_Y } },
   { 0xAE, { 3, 4, INSTR_LDX, Absolute } },
   { 0xBE, { 3, 4 /*+1 if page crossed*/, INSTR_LDX, Absolute_Y } },

   { 0xA0, { 2, 2, INSTR_LDY, Immediate } },
   { 0xA4, { 2, 3, INSTR_LDY, ZeroPage } },
   { 0xB4, { 2, 4, INSTR_LDY, ZeroPage_X } },
   { 0xAC, { 3, 4, INSTR_LDY, Absolute } },
   { 0xBC, { 3, 4 /*+1 if page crossed*/, INSTR_LDY, Absolute_X } },

   { 0x4A, { 1, 2, INSTR_LSR, NoneAddressing } },
   { 0x46, { 2, 5, INSTR_LSR, ZeroPage } },
   { 0x56, { 2, 6, INSTR_LSR, ZeroPage_X } },
   { 0x4E, { 3, 6, INSTR_LSR, Absolute } },
   { 0x5E, { 3, 7, INSTR_LSR, Absolute_X } },

   { 0xEA, { 1, 2, INSTR_NOP, NoneAddressing } },

   { 0x09, { 2, 2, INSTR_ORA, Immediate } },
   { 0x05, { 2, 3, INSTR_ORA, ZeroPage } },
   { 0x15, { 2, 4, INSTR_ORA, ZeroPage_X } },
   { 0x0D, { 3, 4, INSTR_ORA, Absolute } },
   { 0x1D, { 3, 4 /*+1 if page crossed*/, INSTR_ORA, Absolute_X } },
   { 0x19, { 3, 4 /*+1 if page crossed*/, INSTR_ORA, Absolute_Y } },
   { 0x01, { 2, 6, INSTR_ORA, Indirect_X } },
   { 0x11, { 2, 5 /*+1 if page crossed*/, INSTR_ORA, Indirect_Y } },

   { 0x48, { 1, 3, INSTR_PHA, NoneAddressing } },

   { 0x08, { 1, 3, INSTR_PHP, NoneAddressing } },

   { 0x68, { 1, 4, INSTR_PLA, NoneAddressing } },

   { 0x28, { 1, 4, INSTR_PLP, NoneAddressing } },

   { 0x2A, { 1, 2, INSTR_ROL, NoneAddressing } },
   { 0x26, { 2, 5, INSTR_ROL, ZeroPage } },
   { 0x36, { 2, 6, INSTR_ROL, ZeroPage_X } },
   { 0x2E, { 3, 6, INSTR_ROL, Absolute } },
   { 0x3E, { 3, 7, INSTR_ROL, Absolute_X } },

   { 0x6A, { 1, 2, INSTR_ROR, NoneAddressing } },
   { 0x66, { 2, 5, INSTR_ROR, ZeroPage } },
   { 0x76, { 2, 6, INSTR_ROR, ZeroPage_X } },
   { 0x6E, { 3, 6, INSTR_ROR, Absolute } },
   { 0x7E, { 3, 7, INSTR_ROR, Absolute_X } },

   { 0x40, { 1, 6, INSTR_RTI, NoneAddressing } },

   { 0x60, { 1, 6, INSTR_RTS, NoneAddressing } },

   { 0xE9, { 2, 2, INSTR_RTS, Immediate } },
   { 0xE5, { 2, 3, INSTR_RTS, ZeroPage } },
   { 0xF5, { 2, 4, INSTR_RTS, ZeroPage_X } },
   { 0xED, { 3, 4, INSTR_RTS, Absolute } },
   { 0xFD, { 3, 4 /*+1 if page crossed*/, INSTR_RTS, Absolute_X } },
   { 0xF9, { 3, 4 /*+1 if page crossed*/, INSTR_RTS, Absolute_Y } },
   { 0xE1, { 2, 6, INSTR_RTS, Indirect_X } },
   { 0xF1, { 2, 5 /*+1 if page crossed*/, INSTR_RTS, Indirect_Y } },

   { 0x38, { 1, 2, INSTR_SEC, NoneAddressing } },

   { 0xF8, { 1, 2, INSTR_SED, NoneAddressing } },

   { 0x78, { 1, 2, INSTR_SEI, NoneAddressing } },

   { 0x85, { 2, 3, INSTR_STA, ZeroPage } },
   { 0x95, { 2, 4, INSTR_STA, ZeroPage_X } },
   { 0x8D, { 3, 4, INSTR_STA, Absolute } },
   { 0x9D, { 3, 5, INSTR_STA, Absolute_X } },
   { 0x99, { 3, 5, INSTR_STA, Absolute_Y } },
   { 0x81, { 2, 6, INSTR_STA, Indirect_X } },
   { 0x91, { 2, 6, INSTR_STA, Indirect_Y } },

   { 0x86, { 2, 3, INSTR_STX, ZeroPage } },
   { 0x96, { 2, 4, INSTR_STX, ZeroPage_Y } },
   { 0x8E, { 3, 4, INSTR_STX, Absolute } },

   { 0x84, { 2, 3, INSTR_STY, ZeroPage } },
   { 0x94, { 2, 4, INSTR_STY, ZeroPage_X } },
   { 0x8C, { 3, 4, INSTR_STY, Absolute } },

   { 0xAA, { 1, 2, INSTR_TAX, NoneAddressing } },
   { 0xA8, { 1, 2, INSTR_TAY, NoneAddressing } },
   { 0xBA, { 1, 2, INSTR_TSX, NoneAddressing } },
   { 0x8A, { 1, 2, INSTR_TXA, NoneAddressing } },
   { 0x9A, { 1, 2, INSTR_TXS, NoneAddressing } },
   { 0x98, { 1, 2, INSTR_TYA, NoneAddressing } },
};

