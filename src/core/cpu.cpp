#include "cpu.h"

CPU::CPU() {
    // Initialize registers
    registers.PC = MEM_PROGRAM_START;
    registers.SP = 0xFF;
    registers.A  = 0x00;
    registers.X  = 0x00;
    registers.Y  = 0x00;
    registers.P  = 0x00;
}

CPU::~CPU() {
    // Nothing to do here
}

void CPU::reset() {
    // Initialize registers
    registers.PC = memoryReadu16(MEM_RESET_LOCATION);
    registers.SP = 0xFF;
    registers.A  = 0x00;
    registers.X  = 0x00;
    registers.Y  = 0x00;
    registers.P  = 0x00;
}

instruction_t CPU::fetch(uint8_t opcode) {
    return instructionSet.at(opcode);
}

uint16_t CPU::decode(uint8_t arg0, uint8_t arg1, uint8_t mode) {
    switch(mode) {
        case Immediate:
            return (uint16_t) arg0;
        case ZeroPage:
            return (uint16_t) memoryReadu16(arg0);
        case ZeroPage_X:
            return (uint16_t) memoryReadu16(arg0 + registers.X);
        case ZeroPage_Y:
            return (uint16_t) memoryReadu16(arg0 + registers.Y);
        case Absolute:
            return CONCAT(arg0, arg1);
        case Absolute_X:
            return CONCAT(arg0, arg1) + registers.X;
        case Absolute_Y:
            return CONCAT(arg0, arg1) + registers.Y;
        case Indirect:
            return memoryReadu16(CONCAT(arg0, arg1));
        case Indirect_X:
            return memoryReadu16(CONCAT(arg0, arg1)) + registers.X;
        case Indirect_Y:
            return memoryReadu16(CONCAT(arg0, arg1)) + registers.Y;
        case Relative:
            return (int8_t) arg0;
        default:
            return 0x0000; // TODO: Throw error
    }
}


void CPU::exec(instruction_t *instr, uint8_t opcode, uint16_t arg) {
    // Execute instruction
    switch(instr->name) {
        case INSTR_BRK: BRK(instr->mode, arg); break;

        case INSTR_ADC: ADC(instr->mode, arg); break;
        case INSTR_AND: AND(instr->mode, arg); break;
        case INSTR_ASL: ASL(instr->mode, arg); break;
        case INSTR_BCC: BCC(instr->mode, arg); break;
        case INSTR_BCS: BCS(instr->mode, arg); break;
        case INSTR_BEQ: BEQ(instr->mode, arg); break;
        case INSTR_BIT: BIT(instr->mode, arg); break;
        case INSTR_BMI: BMI(instr->mode, arg); break;
        case INSTR_BNE: BNE(instr->mode, arg); break;
        case INSTR_BPL: BPL(instr->mode, arg); break;
        case INSTR_BVC: BVC(instr->mode, arg); break;
        case INSTR_BVS: BVS(instr->mode, arg); break;
        case INSTR_CLC: CLC(instr->mode, arg); break;
        case INSTR_CLD: CLD(instr->mode, arg); break;
        case INSTR_CLI: CLI(instr->mode, arg); break;
        case INSTR_CLV: CLV(instr->mode, arg); break;
        case INSTR_CMP: CMP(instr->mode, arg); break;
        case INSTR_CPX: CPX(instr->mode, arg); break;
        case INSTR_CPY: CPY(instr->mode, arg); break;
        case INSTR_DEC: DEC(instr->mode, arg); break;
        case INSTR_DEX: DEX(instr->mode, arg); break;
        case INSTR_DEY: DEY(instr->mode, arg); break;
        case INSTR_EOR: EOR(instr->mode, arg); break;
        case INSTR_INC: INC(instr->mode, arg); break;
        case INSTR_INX: INX(instr->mode, arg); break;
        case INSTR_INY: INY(instr->mode, arg); break;
        case INSTR_JMP: JMP(instr->mode, arg); break;
        case INSTR_JSR: JSR(instr->mode, arg); break;
        case INSTR_LDA: LDA(instr->mode, arg); break;
        case INSTR_LDX: LDX(instr->mode, arg); break;
        case INSTR_LDY: LDY(instr->mode, arg); break;
        case INSTR_LSR: LSR(instr->mode, arg); break;
        case INSTR_NOP: NOP(instr->mode, arg); break;
        case INSTR_ORA: ORA(instr->mode, arg); break;
        case INSTR_PHA: PHA(instr->mode, arg); break;
        case INSTR_PHP: PHP(instr->mode, arg); break;
        case INSTR_PLA: PLA(instr->mode, arg); break;
        case INSTR_PLP: PLP(instr->mode, arg); break;
        case INSTR_ROL: ROL(instr->mode, arg); break;
        case INSTR_ROR: ROR(instr->mode, arg); break;
        case INSTR_RTI: RTI(instr->mode, arg); break;
        case INSTR_RTS: RTS(instr->mode, arg); break;
        case INSTR_SBC: SBC(instr->mode, arg); break;
        case INSTR_SEC: SEC(instr->mode, arg); break;
        case INSTR_SED: SED(instr->mode, arg); break;
        case INSTR_SEI: SEI(instr->mode, arg); break;
        case INSTR_STA: STA(instr->mode, arg); break;
        case INSTR_STX: STX(instr->mode, arg); break;
        case INSTR_STY: STY(instr->mode, arg); break;
        case INSTR_TAX: TAX(instr->mode, arg); break;
        case INSTR_TAY: TAY(instr->mode, arg); break;
        case INSTR_TSX: TSX(instr->mode, arg); break;
        case INSTR_TXA: TXA(instr->mode, arg); break;
        case INSTR_TXS: TXS(instr->mode, arg); break;
        case INSTR_TYA: TYA(instr->mode, arg); break;

        default: opcode = 0x00; return; // TODO: Throw exception
    }
}

void CPU::run(uint8_t program[], size_t program_size) {
    memoryLoad(program, program_size);
    if(VERBOSE) emscripten_log(EM_LOG_CONSOLE, "program size %u", program_size);

    uint8_t opcode = 0x01; // Initialize to a non-zero value
    
    uint8_t arg0;
    uint8_t arg1;
    uint16_t arg;

    instruction_t instr;

    // TODO: Consider using emscripten_set_main_loop 
    while(opcode) {
        opcode = memory[registers.PC];
        arg0 = memory[registers.PC + 1];
        arg1 = memory[registers.PC + 2];
        if(VERBOSE) emscripten_log(EM_LOG_CONSOLE, "0x%X opcode, 0x%X program counter", opcode, registers.PC);

        // Fetch instruction
        instr = fetch(opcode);
        arg = decode(arg0, arg1, instr.mode);

        exec(&instr, opcode, arg);

        if(VERBOSE) emscripten_log(EM_LOG_CONSOLE, "%u name, %u arg0, %u arg1, %u arg", instr.name, arg0, arg1, arg);
        registers.PC += instr.bytes; // Increment PC by number of bytes in instruction + 1 for opcode
    }
    
}

void CPU::updateCarryFlag(uint8_t result, uint8_t a, uint8_t b) {
    if(result < a || result < b) {
        registers.P |= FLAG_CARRY;
    } else {
        registers.P &= ~FLAG_CARRY;
    }
}

void CPU::updateZeroFlag(uint8_t value) {
    if (value == 0) {
        registers.P |= FLAG_ZERO;
    } else {
        registers.P &= ~FLAG_ZERO;
    }
}

void CPU::updateNegativeFlag(uint8_t value) {
    if (value & 0x80) {
        registers.P |= FLAG_NEGATIVE;
    } else {
        registers.P &= ~FLAG_NEGATIVE;
    }
}

void CPU::updateOverflowFlag(uint8_t result, uint8_t a, uint8_t b) {
    result &= 0b10000000;
    a      &= 0b10000000;
    b      &= 0b10000000;

    registers.P |= ((~a & b & result) | (a & ~b & ~result)) >> 1;
}

void CPU::updateFlags(uint8_t result, uint8_t a, uint8_t b) {
    updateCarryFlag(result, a, b);
    updateZeroFlag(result);
    updateNegativeFlag(result);
    updateOverflowFlag(result, a, b);
}

// Memory
uint8_t CPU::memoryRead(uint16_t address) {
    return memory[address];
}

uint16_t CPU::memoryReadu16(uint16_t address) {
    return CONCAT(memory[address], memory[address + 1]);
}

void CPU::memoryWrite(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void CPU::memoryWriteu16(uint16_t address, uint16_t value) {
    memory[address] = (uint8_t) value;
    memory[address + 1] = (uint8_t) (value >> 8);
}

void CPU::memoryLoad(uint8_t block[], size_t size) {
    // Load array into memory
    uint8_t *start_addr = &memory[MEM_PROGRAM_START];
    memcpy(start_addr, block, size);
}

void CPU::pushStack(uint8_t value) {
    registers.SP--;
    memoryWrite(MEM_SYSTEM_STACK_START + registers.SP, value);

    // TODO: Handle stack overflow
}

void CPU::pushStacku16(uint16_t value) {
    pushStack((uint8_t) (value >> 8));
    pushStack((uint8_t) value);
}

uint8_t CPU::popStack() {
    uint8_t value = memoryRead(MEM_SYSTEM_STACK_START + registers.SP);
    registers.SP++;
    return value;

    // TODO: Don't pop on empty stack
}

uint16_t CPU::popStacku16() {
    uint16_t value = popStack();
    value |= popStack() << 8;
    return value;
}

// Instructions

// Add with Carry
void CPU::ADC(uint8_t mode, uint16_t arg) {
    registers.A += arg + ((uint8_t) (registers.P & FLAG_CARRY) > 0);

    updateFlags(registers.A, arg, (uint8_t) (registers.P & FLAG_CARRY) > 0);
}

// Logical AND
void CPU::AND(uint8_t mode, uint16_t arg) {
    registers.A &= arg;

    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Arithmetic Shift Left
void CPU::ASL(uint8_t mode, uint16_t arg) {
    switch(mode) {
        case NoneAddressing:
            arg = registers.A;
        default:
            registers.P &= ~FLAG_CARRY;
            registers.P |= (arg & 0x80) ? FLAG_CARRY : 0;
            registers.A = arg << 1;
            break;
    }

    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Branch if Carry Clear
void CPU::BCC(uint8_t mode, uint16_t arg) {
    if(!(registers.P & FLAG_CARRY)) registers.PC += arg;
}

// Branch if Carry Set
void CPU::BCS(uint8_t mode, uint16_t arg) {
    if(registers.P & FLAG_CARRY) registers.PC += arg;
}

// Branch if Equal
void CPU::BEQ(uint8_t mode, uint16_t arg) {
    if(registers.P & FLAG_ZERO) registers.PC += arg;
}

// Bit Test
void CPU::BIT(uint8_t mode, uint16_t arg) {
    arg &= registers.A;

    registers.P &= ~FLAG_ZERO & ~FLAG_NEGATIVE & ~FLAG_OVERFLOW;
    registers.P |= (arg & (FLAG_NEGATIVE | FLAG_OVERFLOW));
    updateZeroFlag(arg);
    
}

// Branch if Minus
void CPU::BMI(uint8_t mode, uint16_t arg) {
    if(registers.P & FLAG_NEGATIVE) registers.PC += arg;
}

// Branch if Not Equal
void CPU::BNE(uint8_t mode, uint16_t arg) {
    if(!(registers.P & FLAG_ZERO)) registers.PC += arg;
}

// Branch if Positive
void CPU::BPL(uint8_t mode, uint16_t arg) {
    if(!(registers.P & FLAG_NEGATIVE)) registers.PC += arg;
}

// Force interrupt
void CPU::BRK(uint8_t mode, uint16_t arg) {
    // TODO: Add stack and interrupts

    // registers.PC += 2;
    // pushStack(registers.PC >> 8);
    // pushStack(registers.PC & 0xFF);
    // pushStack(registers.P);
    // registers.P |= FLAG_INTERRUPT;
    // registers.PC = memoryReadu16(0xFFFE);

    registers.P |= FLAG_BREAK;
}

// Branch if Overflow Clear
void CPU::BVC(uint8_t mode, uint16_t arg) {
    if(!(registers.P & FLAG_OVERFLOW)) registers.PC += arg;
}

// Branch if Overflow Set
void CPU::BVS(uint8_t mode, uint16_t arg) {
    if(registers.P & FLAG_OVERFLOW) registers.PC += arg;
}

// Clear Carry Flag
void CPU::CLC(uint8_t mode, uint16_t arg) {
    registers.P &= ~FLAG_CARRY;
}

// Clear Decimal Mode
void CPU::CLD(uint8_t mode, uint16_t arg) {
    registers.P &= ~FLAG_DECIMAL;
}

// Clear Interrupt Disable
void CPU::CLI(uint8_t mode, uint16_t arg) {
    registers.P &= ~FLAG_INTERRUPT;
}

// Clear Overflow Flag
void CPU::CLV(uint8_t mode, uint16_t arg) {
    registers.P &= ~FLAG_OVERFLOW;
}

// Compare
void CPU::CMP(uint8_t mode, uint16_t arg) {
    if(registers.A == arg) {
        registers.P |= FLAG_ZERO | FLAG_CARRY;
    } else if(registers.A >= arg) {
        registers.P |= FLAG_CARRY;
    }

    updateNegativeFlag(registers.A - arg);
}

// Compare X register
void CPU::CPX(uint8_t mode, uint16_t arg) {
    if(registers.X == arg) {
        registers.P |= FLAG_ZERO | FLAG_CARRY;
    } else if(registers.X >= arg) {
        registers.P |= FLAG_CARRY;
    }

    updateNegativeFlag(registers.X - arg);
}

// Compare Y register
void CPU::CPY(uint8_t mode, uint16_t arg) {
    if(registers.Y == arg) {
        registers.P |= FLAG_ZERO | FLAG_CARRY;
    } else if(registers.Y >= arg) {
        registers.P |= FLAG_CARRY;
    }

    updateNegativeFlag(registers.Y - arg);
}

// Decrement Memory
void CPU::DEC(uint8_t mode, uint16_t arg) {
    uint8_t value = ((uint8_t) arg) - 1;
    memoryWrite(arg, value);

    updateZeroFlag(value);
    updateNegativeFlag(value);
}

// Decrement X Register
void CPU::DEX(uint8_t mode, uint16_t arg) {
    registers.X--;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

// Decrement Y Register
void CPU::DEY(uint8_t mode, uint16_t arg) {
    registers.Y--;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

// Exclusive OR
void CPU::EOR(uint8_t mode, uint16_t arg) {
    registers.A ^= arg;
    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Increment Memory
void CPU::INC(uint8_t mode, uint16_t arg) {
    uint8_t value = ((uint8_t) arg) - 1;
    memoryWrite(arg, value);

    updateZeroFlag(value);
    updateNegativeFlag(value);
}

// Increment X Register
void CPU::INX(uint8_t mode, uint16_t arg) {
    registers.X++;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

// Increment Y Register
void CPU::INY(uint8_t mode, uint16_t arg) {
    registers.Y++;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

// Jump
void CPU::JMP(uint8_t mode, uint16_t arg) {
    switch(mode) {
        case Absolute:
            registers.PC = arg;
            break;
        case Indirect:
            registers.PC = memoryReadu16(arg);
            break;
    }
}

// Jump to Subroutine
void CPU::JSR(uint8_t mode, uint16_t arg) {
    registers.PC--;
    pushStacku16(registers.PC);
    registers.PC = arg;
}

// Load Accumulator
void CPU::LDA(uint8_t mode, uint16_t arg) {
    registers.A = (uint8_t) arg;
    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Load X Register
void CPU::LDX(uint8_t mode, uint16_t arg) {
    registers.X = (uint8_t) arg;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

// Load Y Register
void CPU::LDY(uint8_t mode, uint16_t arg) {
    registers.Y = (uint8_t) arg;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

// Logical Shift Right
void CPU::LSR(uint8_t mode, uint16_t arg) {
    switch(mode) {
        case NoneAddressing:
            arg = registers.A;
        default:
            registers.P &= ~FLAG_CARRY;
            registers.P |= (arg & 0x01) ? FLAG_CARRY : 0;
            registers.A = arg >> 1;
            break;
    }

    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// No Operation
void CPU::NOP(uint8_t mode, uint16_t arg) {
    // Do nothing
}

// Logical Inclusive OR
void CPU::ORA(uint8_t mode, uint16_t arg) {
    registers.A |= arg;
    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Push Accumulator
void CPU::PHA(uint8_t mode, uint16_t arg) {
    pushStack(registers.A);
}

// Push Processor Status
void CPU::PHP(uint8_t mode, uint16_t arg) {
    pushStack(registers.P);
}

// Pull Accumulator
void CPU::PLA(uint8_t mode, uint16_t arg) {
    registers.A = popStack();
    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

// Pull Processor Status
void CPU::PLP(uint8_t mode, uint16_t arg) {
    registers.P = popStack();
}

void CPU::ROL(uint8_t mode, uint16_t arg) {}
void CPU::ROR(uint8_t mode, uint16_t arg) {}
void CPU::RTI(uint8_t mode, uint16_t arg) {}
void CPU::RTS(uint8_t mode, uint16_t arg) {}
void CPU::SBC(uint8_t mode, uint16_t arg) {}
void CPU::SEC(uint8_t mode, uint16_t arg) {}
void CPU::SED(uint8_t mode, uint16_t arg) {}
void CPU::SEI(uint8_t mode, uint16_t arg) {}

// Store accumulator
void CPU::STA(uint8_t mode, uint16_t arg) {
    memoryWrite(arg, registers.A);
}

// Store X
void CPU::STX(uint8_t mode, uint16_t arg) {
    memoryWrite(arg, registers.X);
}

// Store Y
void CPU::STY(uint8_t mode, uint16_t arg) {
    memoryWrite(arg, registers.Y);
}

// Transfer Accumulator to X
void CPU::TAX(uint8_t mode, uint16_t arg) {
    registers.X = registers.A;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

// Transfer Accumulator to Y
void CPU::TAY(uint8_t mode, uint16_t arg) {
    registers.Y = registers.A;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

void CPU::TSX(uint8_t mode, uint16_t arg) {}

// Transfer X to Accumulator
void CPU::TXA(uint8_t mode, uint16_t arg) {
    registers.A = registers.X;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

void CPU::TXS(uint8_t mode, uint16_t arg) {}

// Transfer Y to Accumulator
void CPU::TYA(uint8_t mode, uint16_t arg) {
    registers.A = registers.Y;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}