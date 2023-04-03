#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../aids.h"


#define OP_HALT 99
#define OP_ADD 1
#define OP_MUL 2

typedef struct IntcodeProgram {
    int32_t *mem;
    size_t length;
    size_t counter;
} IntcodeProgram;

void ip_parse(char *str, IntcodeProgram *program);
void ip_destroy(IntcodeProgram *program);
int32_t ip_consume(IntcodeProgram *program);
int32_t ip_peek(IntcodeProgram *program);
int32_t ip_peek_pos(IntcodeProgram *program, size_t pos);
void ip_memset(IntcodeProgram *program, size_t pos, int32_t val);

void part1(IntcodeProgram *program, char **output);
void part2(IntcodeProgram *program, char **output);

int main() {
    char *data;
    read_file("./input", &data);
    IntcodeProgram intcodeProgram;

    ip_parse(data, &intcodeProgram);

    char *part1_output;
    char *part2_output;
    part1(&intcodeProgram, &part1_output);
    part2(&intcodeProgram, &part2_output);

    printf("Part 1: %s\n", part1_output);
    printf("Part 2: %s\n", part2_output);

    ip_destroy(&intcodeProgram);
    return 0;
}

bool is_comma(char c) {
    return c == ',';
}

void ip_parse(char *str, IntcodeProgram *intcodeProgram) {
    size_t len = str_count_if(str, is_comma) + 1;
    int32_t *insts = malloc(sizeof(int32_t) * len);
    size_t i = 0;

    while (*str != '\0') {
        str_skip_while(&str, is_whitespace);

        insts[i] = strtoll(str, &str, 10);
        i += 1;

        str_skip_while(&str, is_whitespace);

        if (*str == '\0') {
            break;
        }

        if (*str != ',') {
            PANIC("Unexpected character %c", *str);
        }

        str += 1;
    }

    intcodeProgram->length = i;
    intcodeProgram->mem = insts;
}

void ip_destroy(IntcodeProgram *intcodeProgram) {
    free((void *) intcodeProgram->mem);
}

int32_t ip_peek(IntcodeProgram *program) {
    return ip_peek_pos(program, program->counter);
}

int32_t ip_peek_pos(IntcodeProgram *program, size_t pos) {
    return program->mem[pos];
}

int32_t ip_consume(IntcodeProgram *program) {
    return ip_peek_pos(program, program->counter++);
}

void ip_memset(IntcodeProgram *program, size_t pos, int32_t val) {
    program->mem[pos] = val;
}

void part1(IntcodeProgram *ip, char **output) {
    // IMPORTANT NOTE: Remove the following 2 lines when running the example input
    ip_memset(ip, 1, 12);
    ip_memset(ip, 2, 2);

    while (ip_peek(ip) != OP_HALT) {
        int32_t opcode = ip_consume(ip);

        switch (opcode) {
            case OP_ADD: {
                int32_t a = ip_peek_pos(ip, ip_consume(ip));
                int32_t b = ip_peek_pos(ip, ip_consume(ip));
                int32_t output_pos = ip_consume(ip);
                ip_memset(ip, output_pos, a + b);
            };
            break;

            case OP_MUL: {
                int32_t a = ip_peek_pos(ip, ip_consume(ip));
                int32_t b = ip_peek_pos(ip, ip_consume(ip));
                int32_t output_pos = ip_consume(ip);
                ip_memset(ip, output_pos, a * b);
            };
            break;

            default: {
                PANIC("Unsupported opcode %d", opcode);
            };
        }
    }

    int32_t result = ip_peek_pos(ip, 0);

    size_t len = snprintf(NULL, 0, "%d", result);
    *output = malloc(sizeof(char) * (len + 1));
    snprintf(*output, len + 1, "%d", result);
}

void part2(IntcodeProgram *ip, char **output) {
    // snprintf(*output, len + 1, "%lu", sum);
}
