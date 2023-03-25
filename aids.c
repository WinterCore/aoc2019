#include <stdlib.h>
#include <stdio.h>
#include "aids.h"

void read_file(char *path, char **data) {
    FILE *fd = fopen(path, "r");

    if (fd == NULL) {
        perror("[ERROR]: Failed to read input file");
        exit(EXIT_FAILURE);
    }

    fseek(fd, 0, SEEK_END);
    size_t length = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char *buffer = malloc(length + 1);

    if (buffer) {
        fread(buffer, 1, length, fd);
    }

    buffer[length] = '\0';

    *data = buffer;
}

size_t str_skip_while(char **str, bool (*predicate)(char)) {
    size_t n = 0;

    char *p = *str;

    while (p[n] != '\0' && predicate(p[n])) {
        n += 1;
    }

    *str += n;

    return n;
}

size_t str_count_if(char *str, bool (*predicate)(char)) {
    size_t n = 0;

    while (*str != '\0') {
        if (predicate(*str)) {
            n += 1;
        }

        str += 1;
    }
    
    return n;
}

bool is_whitespace(char c) {
    return is_space(c) || is_newline(c) || is_tab(c);
}

bool is_space(char c) {
    return c == ' ';
}

bool is_tab(char c) {
    return c == '\t';
}

bool is_newline(char c) {
    return c == '\n';
}

bool is_eof(char c) {
    return c == EOF;
}
