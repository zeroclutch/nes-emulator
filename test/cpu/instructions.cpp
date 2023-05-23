// Dependencies
#include <emscripten.h>
#include <assert.h>

#include "../../src/core/instructions.h"
#include "../../src/core/cpu.h"

void validate(bool condition, const char *func) {
    if(condition) {
        emscripten_log(EM_LOG_CONSOLE, "    %s passed", func);
    } else {
        emscripten_log(EM_LOG_CONSOLE, "!!! %s failed", func);
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
    cpu.run(program, sizeof(program));

    // Assert that the accumulator contains the correct value
    validate(cpu.registers.A == 0x20, __func__);
}

void test_adc_add_with_carry() {
    CPU cpu;


    uint8_t program[] = {
        0x69, // ADC Imm
        0xD0,
        0x69, // ADC Imm
        0x90,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_CARRY, __func__);
}

void test_adc_add_with_overflow() {
    CPU cpu;


    uint8_t program[] = {
        0x69, // ADC Imm
        0xD0,
        0x69, // ADC Imm
        0x90,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_OVERFLOW, __func__);
}

void test_and_with_immediate() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0x8F,
        0x29, // AND Imm
        0xFA,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.A == 0x8A, __func__);
}

void test_and_negative_flag() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0xFF,
        0x29, // AND Imm
        0x80,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_and_zero_flag() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0xFF,
        0x29, // AND Imm
        0x00,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_asl_shift_accumulator() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0xF8,
        0x0A, // ASL Accumulator
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.A == 0xF0, __func__);
}

void test_asl_shift_with_carry() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0xF8,
        0x0A, // ASL Accumulator
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_CARRY, __func__);
}

void test_lda_immediate_load_data() {
    CPU cpu;


    uint8_t program[] = {
        0xA9, // LDA Imm
        0x42,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.A == 0x42, __func__);
}

void test_lda_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_lda_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x80,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_ldx_immediate_load_data() {
    CPU cpu;


    uint8_t program[] = {
        0xA2, // LDX Imm
        0x42,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.X == 0x42, __func__);
}

void test_ldx_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_ldx_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x80,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_ldy_immediate_load_data() {
    CPU cpu;


    uint8_t program[] = {
        0xA0, // LDY Imm
        0x42,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.Y == 0x42, __func__);
}

void test_ldy_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_ldy_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x80,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_sta_store_accumulator_with_absolute() {
    CPU cpu;

    uint8_t oldValue0 = cpu.memoryRead(0x0500);

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x42,
        0x8D, // STA Absolute
        0x00,
        0x05,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x42, __func__);

    // Cleanup
    cpu.memoryWrite(0x0500, oldValue0);
}

void test_sta_store_accumulator_zero_page() {
    CPU cpu;

    uint8_t oldValue0 = cpu.memoryRead(0x00CD);
    uint8_t oldValue1 = cpu.memoryRead(0x0500);
    cpu.memoryWrite(0x00CD, (uint8_t) 0x00);
    cpu.memoryWrite(0x00CE, (uint8_t) 0x05);

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x42,
        0x85, // STA ZeroPage
        0xCD,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x42, __func__);
    
    // Cleanup
    cpu.memoryWrite(0x00CD, oldValue0);
    cpu.memoryWrite(0x0500, oldValue1);
}

void test_stx_store_x_with_absolute() {
    CPU cpu;

    uint8_t oldValue0 = cpu.memoryRead(0x0500);

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x43,
        0x8E, // STX Absolute
        0x00,
        0x05,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x43, __func__);

    // Cleanup
    cpu.memoryWrite(0x0500, oldValue0);
}

void test_stx_store_x_with_zero_page() {
    CPU cpu;

    // Setup
    uint16_t oldValue0 = cpu.memoryReadu16(0x00CD);
    uint8_t  oldValue1 = cpu.memoryRead(0x0500);
    cpu.memoryWriteu16(0x00CD, 0x0500);

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x43,
        0x86, // STX ZeroPage
        0xCD,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x43, __func__);

    // Cleanup
    cpu.memoryWriteu16(0x00CD, oldValue0);
    cpu.memoryWrite(0x0500, oldValue1);
}

void test_sty_store_y_with_absolute() {
    CPU cpu;

    // Setup
    uint16_t oldValue0 = cpu.memoryReadu16(0x0500);

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x44,
        0x8C, // STY Absolute
        0x00,
        0x05,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x44, __func__);

    // Cleanup
    cpu.memoryWriteu16(0x0500, oldValue0);
}

void test_sty_store_y_with_zero_page() {
    CPU cpu;

    // Setup
    uint16_t oldValue0 = cpu.memoryReadu16(0x00CD);
    uint8_t  oldValue1 = cpu.memoryRead(0x0500);
    cpu.memoryWriteu16(0x00CD, 0x0500);

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x44,
        0x84, // STY ZeroPage
        0xCD,
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

    validate(cpu.memoryRead(0x0500) == 0x44, __func__);

    // Cleanup
    cpu.memoryWriteu16(0x00CD, oldValue0);
    cpu.memoryWrite(0x0500, oldValue1);
}

void test_tax_move_a_to_x() {
    CPU cpu;

    uint8_t program[] = {
        0xAA, // TAX
        0x00, // BRK
    };

    cpu.run(program, sizeof(program));

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

    cpu.run(program, sizeof(program));

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
    
    cpu.run(program, sizeof(program));

    validate(cpu.registers.X == 0x01, __func__);
}

int main() {
    test_adc_add_with_immediate();
    test_adc_add_with_carry();
    test_adc_add_with_overflow();

    test_and_with_immediate();
    test_and_negative_flag();
    test_and_zero_flag();

    test_asl_shift_accumulator();
    test_asl_shift_with_carry();

    test_lda_immediate_load_data();
    test_lda_zero_flag();
    test_lda_negative_flag();

    test_ldx_immediate_load_data();
    test_ldx_zero_flag();
    test_ldx_negative_flag();

    test_ldy_immediate_load_data();
    test_ldy_zero_flag();
    test_ldy_negative_flag();

    test_sta_store_accumulator_with_absolute();
    test_sta_store_accumulator_zero_page();
    
    test_stx_store_x_with_absolute();
    test_stx_store_x_with_zero_page();
    
    test_sty_store_y_with_absolute();
    test_sty_store_y_with_zero_page();

    test_tax_move_a_to_x();
    test_inx_overflow();

    test_5_ops_working_together();
}