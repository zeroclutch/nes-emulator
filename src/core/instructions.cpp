#include "instructions.h"

std::map<uint8_t, instruction_t> instructionSet = {
   { 0x00, { 1, 7, INSTR_BRK, Implied   } },

   { 0xA9, { 2, 2, INSTR_LDA, Immediate  } },
   { 0xA5, { 2, 3, INSTR_LDA, ZeroPage   } },
   { 0xB5, { 2, 4, INSTR_LDA, ZeroPage_X } },
   { 0xAD, { 3, 4, INSTR_LDA, Absolute   } },
   { 0xBD, { 3, 4, INSTR_LDA, Absolute_X } },
   { 0xB9, { 3, 4, INSTR_LDA, Absolute_Y } },
   { 0xA1, { 2, 6, INSTR_LDA, Indirect_X } },
   { 0xB1, { 2, 5, INSTR_LDA, Indirect_Y } },

   { 0xA2, { 2, 2, INSTR_LDX, Immediate } },

   { 0xA0, { 2, 2, INSTR_LDY, Immediate } },

   { 0xE8, { 1, 2, INSTR_INX, Implied   } },

   { 0xC8, { 1, 2, INSTR_INY, Implied   } },

   { 0xAA, { 1, 2, INSTR_TAX, Implied   } }
};
