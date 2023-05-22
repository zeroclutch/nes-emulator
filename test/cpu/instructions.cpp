// Dependencies
#include <emscripten.h>
#include <assert.h>

#include "../../src/core/instructions.h"
#include "../../src/core/cpu.h"

void validate(bool condition, const char *func) {
    if(condition) {
        emscripten_log(EM_LOG_CONSOLE, "%s passed", func);
    } else {
        emscripten_log(EM_LOG_CONSOLE, "%s failed", func);
    }
}

void test_adc_add_with_immediate() {
    // Create a CPU
    CPU cpu;

    // Load program into memory
    uint8_t program[] = {
        0x69, // ADC Imm
        0x10,
        0x69, // ADC Imm
        0x10,
        0x00, // BRK
    };

    // Execute program
    cpu.exec(program);

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.A == 0x20, __func__);
}

void test_adc_add_with_carry() {
    // Create a CPU
    CPU cpu;

    // Load program into memory
    uint8_t program[] = {
        0x69, // ADC Imm
        0xD0,
        0x69, // ADC Imm
        0x90,
        0x00, // BRK
    };

    // Execute program
    cpu.exec(program);

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.P & FLAG_CARRY, __func__);
}

void test_adc_add_with_overflow() {
    // Create a CPU
    CPU cpu;

    // Load program into memory
    uint8_t program[] = {
        0x69, // ADC Imm
        0xD0,
        0x69, // ADC Imm
        0x90,
        0x00, // BRK
    };

    // Execute program
    cpu.exec(program);

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.P & FLAG_OVERFLOW, __func__);
}

void test_adc_add_with_immediate() {
    // Create a CPU
    CPU cpu;

    // Load program into memory
    uint8_t program[] = {
        0x69, // ADC Imm
        0x10,
        0x69, // ADC Imm
        0x10,
        0x00, // BRK
    };

    // Execute program
    cpu.exec(program);

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.A == 0x20, __func__);
}

void test_lda_immediate_load_data() {
    // Create a CPU
    CPU cpu;

    // Load program into memory
    uint8_t program[] = {
        0xA9, // LDA Imm
        0x42,
        0x00, // BRK
    };

    // Execute program
    cpu.exec(program);

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.A == 0x42, __func__);
}

void test_lda_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.exec(program);

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}


void test_lda_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x80,
        0x00, // BRK
    };

    cpu.exec(program);

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_tax_move_a_to_x() {
    CPU cpu;

    uint8_t program[] = {
        0xAA, // TAX
        0x00, // BRK
    };

    cpu.exec(program);

    validate(cpu.registers.A == cpu.registers.X, __func__);
}

void test_5_ops_working_together() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0xC0,
        0xAA, // TAX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.exec(program);

    validate(cpu.registers.X == 0xC1, __func__);
}

void test_inx_overflow() {
    CPU cpu;

    cpu.registers.X = 0xff;

    uint8_t program[] = {
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };
    
    cpu.exec(program);

    validate(cpu.registers.X == 0x01, __func__);
}

int main() {
    test_adc_add_with_immediate();
    test_adc_add_with_carry();
    test_adc_add_with_overflow();

    test_lda_immediate_load_data();
    test_lda_zero_flag();

    test_tax_move_a_to_x();
    test_inx_overflow();

    test_5_ops_working_together();
}