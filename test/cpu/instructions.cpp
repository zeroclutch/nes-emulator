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
    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_CARRY, __func__);
}

void test_asl_shift_with_zero() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x80,
        0x0A, // ASL Accumulator
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_asl_shift_with_negative() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x40,
        0x0A, // ASL Accumulator
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_bcc_branch_forward() {
    CPU cpu;

    uint8_t program[] = {
        0x90, // BCC
        0x02,
        0xE8, // INX
        0x00, // BRK
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x01, __func__);
}

void test_bcc_branch_reverse() {
    CPU cpu;

    uint8_t program[] = {
        0x90, // BCC
        0x03, // +3
        0xE8, // INX
        0x90, // BCC
        0x02, // +2
        0x90, // BCC
        0xFB, // -5
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x01, __func__);
}

void test_bcc_no_branch_with_carry_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_CARRY;

    uint8_t program[] = {
        0x90, // BCC
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_bcs_branch_with_carry_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_CARRY;

    uint8_t program[] = {
        0xB0, // BCS
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}


void test_bcs_branch_with_carry_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_CARRY;

    uint8_t program[] = {
        0xB0, // BCS
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_beq_branch_with_zero_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_ZERO;

    uint8_t program[] = {
        0xF0, // BEQ
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_beq_branch_with_zero_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_ZERO;

    uint8_t program[] = {
        0xF0, // BEQ
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_bit_zero_page() {
    CPU cpu;

    uint8_t oldValue0 = cpu.memoryRead(0x42);
    cpu.memoryWrite(0x42, 0xFF);

    cpu.registers.A = 0x7F;

    uint8_t program[] = {
        0x24, // BIT Zero Page
        0x42,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_ZERO)
             && !(cpu.registers.P & FLAG_NEGATIVE)
             && cpu.registers.P & FLAG_OVERFLOW, __func__);
    
    cpu.memoryWrite(0x42, oldValue0);
}

void test_bit_absolute() {
    CPU cpu;

    uint8_t oldValue0 = cpu.memoryRead(0x4242);
    cpu.memoryWrite(0x4242, 0xFF);

    cpu.registers.A = 0x7F;

    uint8_t program[] = {
        0x2C, // BIT Absolute
        0x42,
        0x42,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_ZERO)
             && !(cpu.registers.P & FLAG_NEGATIVE)
             && cpu.registers.P & FLAG_OVERFLOW, __func__);
    
    cpu.memoryWrite(0x4242, oldValue0);
}

void test_bmi_branch_with_negative_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_NEGATIVE;

    uint8_t program[] = {
        0x30, // BMI
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_bmi_branch_with_negative_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_NEGATIVE;

    uint8_t program[] = {
        0x30, // BMI
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_bne_branch_with_zero_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_ZERO;

    uint8_t program[] = {
        0xD0, // BNE
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_bne_branch_with_zero_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_ZERO;

    uint8_t program[] = {
        0xD0, // BNE
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_bpl_branch_with_negative_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_NEGATIVE;

    uint8_t program[] = {
        0x10, // BPL
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_bpl_branch_with_negative_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_NEGATIVE;

    uint8_t program[] = {
        0x10, // BPL
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_brk() {
    CPU cpu;

    uint8_t program[] = {
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_BREAK, __func__);
}

void test_bvc_branch_with_overflow_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_OVERFLOW;

    uint8_t program[] = {
        0x50, // BVC
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_bvc_branch_with_overflow_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_OVERFLOW;

    uint8_t program[] = {
        0x50, // BVC
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_bvs_branch_with_overflow_set() {
    CPU cpu;

    cpu.registers.P |= FLAG_OVERFLOW;

    uint8_t program[] = {
        0x70, // BVS
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x00, __func__);
}

void test_bvs_branch_with_overflow_clear() {
    CPU cpu;

    cpu.registers.P &= ~FLAG_OVERFLOW;

    uint8_t program[] = {
        0x70, // BVS
        0x02, // +2
        0xE8, // INX
        0xE8, // INX
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x02, __func__);
}

void test_clc() {
    CPU cpu;

    cpu.registers.P |= FLAG_CARRY;

    uint8_t program[] = {
        0x18, // CLC
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_CARRY), __func__);
}

void test_cld() {
    CPU cpu;

    cpu.registers.P |= FLAG_DECIMAL;

    uint8_t program[] = {
        0xD8, // CLD
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_DECIMAL), __func__);
}

void test_cli() {
    CPU cpu;

    cpu.registers.P |= FLAG_INTERRUPT;

    uint8_t program[] = {
        0x58, // CLI
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_INTERRUPT), __func__);
}

void test_clv() {
    CPU cpu;

    cpu.registers.P |= FLAG_OVERFLOW;

    uint8_t program[] = {
        0xB8, // CLV
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(!(cpu.registers.P & FLAG_OVERFLOW), __func__);
}

void test_lda_immediate_load_data() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x42,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.A == 0x42, __func__);
}

void test_lda_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_lda_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA9, // LDA Imm
        0x80,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_ldx_immediate_load_data() {
    CPU cpu;


    uint8_t program[] = {
        0xA2, // LDX Imm
        0x42,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.X == 0x42, __func__);
}

void test_ldx_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_ldx_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA2, // LDX Imm
        0x80,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_NEGATIVE, __func__);
}

void test_ldy_immediate_load_data() {
    CPU cpu;


    uint8_t program[] = {
        0xA0, // LDY Imm
        0x42,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.Y == 0x42, __func__);
}

void test_ldy_zero_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x00,
        0x00, // BRK
    };
    
    cpu.load_and_run(program, sizeof(program));

    validate(cpu.registers.P & FLAG_ZERO, __func__);
}

void test_ldy_negative_flag() {
    CPU cpu;

    uint8_t program[] = {
        0xA0, // LDY Imm
        0x80,
        0x00, // BRK
    };

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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

    cpu.load_and_run(program, sizeof(program));

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
    
    cpu.load_and_run(program, sizeof(program));

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

    test_bcc_branch_forward();
    test_bcc_branch_reverse();

    test_bcs_branch_with_carry_set();
    test_bcs_branch_with_carry_clear();

    test_beq_branch_with_zero_set();
    test_beq_branch_with_zero_clear();
    
    test_bit_zero_page();

    test_bmi_branch_with_negative_set();
    test_bmi_branch_with_negative_clear();

    test_bne_branch_with_zero_set();
    test_bne_branch_with_zero_clear();

    test_bpl_branch_with_negative_set();
    test_bpl_branch_with_negative_clear();

    test_brk();

    test_bvc_branch_with_overflow_clear();
    test_bvc_branch_with_overflow_set();

    test_bvs_branch_with_overflow_set();
    test_bvs_branch_with_overflow_clear();

    test_clc();

    test_cld();

    test_cli();

    test_clv();


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