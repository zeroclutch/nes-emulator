#include "cpu.h"

CPU::CPU() {
    // Initialize registers
    registers.PC = 0x00;
    registers.SP = 0x00;
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
    registers.PC = memoryReadu16(0xFFFC);
    registers.SP = 0x00;
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
            return (uint16_t) memoryRead(arg0);
        case ZeroPage_X:
            return (uint16_t) memoryRead(arg0 + registers.X);
        case ZeroPage_Y:
            return (uint16_t) memoryRead(arg0 + registers.Y);
        case Absolute:
            return ((arg0 << 8) | arg1);
        case Absolute_X:
            return ((arg0 << 8) | arg1) + registers.X;
        case Absolute_Y:
            return ((arg0 << 8) | arg1) + registers.Y;
        case Indirect:
            return memoryRead((arg0 << 8) | arg1);
        case Indirect_X:
            return memoryRead(((arg0 << 8) | arg1)) + registers.X;
        case Indirect_Y:
            return memoryRead(((arg0 << 8) | arg1)) + registers.Y;
        default:
            return 0x0000; // TODO: Throw error
    }
}

void CPU::exec(uint8_t program[]) {
    uint8_t opcode = 0x01; // Initialize to a non-zero value
    
    uint8_t arg0;
    uint8_t arg1;
    uint16_t arg;
    
    instruction_t instr;
    instr_handler_t fn;
    
    while(opcode) {
        //**
        opcode = program[registers.PC];
        arg0 = program[registers.PC + 1];
        arg1 = program[registers.PC + 2];
        emscripten_log(EM_LOG_CONSOLE, "0x%X opcode", opcode);

        // Fetch instruction
        instr = fetch(opcode);
        arg = decode(arg0, arg1, instr.mode);

        // Execute instruction
        switch(instr.name) {
            case INSTR_BRK: opcode = 0x00; break;
            case INSTR_LDA: LDA(instr.mode, arg); break;
            case INSTR_LDX: LDX(instr.mode, arg); break;
            case INSTR_LDY: LDY(instr.mode, arg); break;
            case INSTR_INX: INX(instr.mode, arg); break;
            case INSTR_INY: INY(instr.mode, arg); break;
            case INSTR_TAX: TAX(instr.mode, arg); break;
            default: opcode = 0x00; return;
        }

        emscripten_log(EM_LOG_CONSOLE, "%u name, %u arg0, %u arg1, %u arg", instr.name, arg0, arg1, arg);

        registers.PC += instr.bytes; // Increment PC by number of bytes in instruction + 1 for opcode
        //*/
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

// Memory
uint8_t CPU::memoryRead(uint16_t address) {
    return memory[address];
}

void CPU::memoryWrite(uint16_t address, uint8_t value) {
    memory[address] = value;
}

void CPU::memoryLoad(uint8_t program[]) {
    // Load program into memory
    uint8_t *start_addr = memory + 0x80;
    memcpy(start_addr, program, sizeof(program));
}

uint16_t CPU::memoryReadu16(uint16_t address) {
    return (memory[address] << 8) | memory[address + 1];
}

// Instructions
void CPU::LDA(uint8_t mode, uint16_t arg) {
    // Load Accumulator
    registers.A = (uint8_t) arg;
    updateZeroFlag(registers.A);
    updateNegativeFlag(registers.A);
}

void CPU::LDX(uint8_t mode, uint16_t arg) {
    // Load X Register
    registers.X = (uint8_t) arg;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

void CPU::LDY(uint8_t mode, uint16_t arg) {
    // Load Y Register
    registers.Y = (uint8_t) arg;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

void CPU::INX(uint8_t mode, uint16_t arg) {
    // Increment X Register
    registers.X++;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}

void CPU::INY(uint8_t mode, uint16_t arg) {
    // Increment X Register
    registers.Y++;
    updateZeroFlag(registers.Y);
    updateNegativeFlag(registers.Y);
}

void CPU::TAX(uint8_t mode, uint16_t arg) {
    // Transfer Accumulator to X
    registers.X = registers.A;
    updateZeroFlag(registers.X);
    updateNegativeFlag(registers.X);
}