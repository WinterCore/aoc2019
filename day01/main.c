#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../aids.h"

typedef struct InputData {
    unsigned long *masses;
    size_t masses_len;
} InputData;

void parse(char *str, InputData *parsedInput);
void part1(InputData *parsedInput, char **output);
void part2(InputData *parsedInput, char **output);

int main() {
    char *data;
    read_file("./input", &data);

    InputData parsedInput;
    parse(data, &parsedInput);

    char *part1_output;
    char *part2_output;
    part1(&parsedInput, &part1_output);
    part2(&parsedInput, &part2_output);

    printf("Part 1: %s\n", part1_output);
    printf("Part 2: %s\n", part2_output);

    return 0;
}

void parse(char *str, InputData *parsedInput) {
    size_t len = str_count_if(str, is_newline);
    unsigned long *buffer = malloc(sizeof(unsigned long) * len);
    size_t i = 0;

    str_skip_while(&str, is_whitespace);

    while (*str != '\0') {

        buffer[i] = strtoll(str, &str, 10);
        i += 1;

        str_skip_while(&str, is_whitespace);
    }

    parsedInput->masses_len = len;
    parsedInput->masses = malloc(i * sizeof(unsigned long));
    memcpy(parsedInput->masses, buffer, i * sizeof(unsigned long));

    free(buffer);
}

void part1(InputData *pi, char **output) {
    u_int64_t sum = 0;

    for (size_t i = 0; i < pi->masses_len; i += 1) {
        sum += pi->masses[i] / 3 - 2;
    }

    size_t len = snprintf(NULL, 0, "%lu", sum);
    *output = malloc(sizeof(char) * (len + 1));
    snprintf(*output, len + 1, "%lu", sum);
}

u_int64_t get_required_fuel_recursive(unsigned long mass) {
    int64_t val = mass / 3 - 2;

    return val <= 0 ? 0 : val + get_required_fuel_recursive(val);
}

void part2(InputData *pi, char **output) {
    u_int64_t sum = 0;

    for (size_t i = 0; i < pi->masses_len; i += 1) {
        sum += get_required_fuel_recursive(pi->masses[i]);
    }

    size_t len = snprintf(NULL, 0, "%lu", sum);
    *output = malloc(sizeof(char) * (len + 1));
    snprintf(*output, len + 1, "%lu", sum);
}
