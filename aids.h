#ifndef AIDS
#define AIDS
#include <stddef.h>
#include <stdbool.h>

#define UNIMPLEMENTED \
    fprintf(stderr, "UNIMPLEMENTED"); \
    exit(EXIT_FAILURE);

#define UNREACHABLE \
    fprintf(stderr, "UNREACHABLE"); \
    exit(EXIT_FAILURE);

#define PANIC(...) \
    fprintf(stderr, "[PANIC]: "); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    exit(EXIT_FAILURE);

#define DEBUG(...) \
    fprintf(stdout, "[DEBUG]: "); \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "\n"); \
    fflush(stdout);

void read_file(char *path, char **data);

size_t str_skip_while(char **str, bool (*predicate)(char));
size_t str_count_if(char *str, bool (*predicate)(char));

bool is_whitespace(char c);
bool is_space(char c);
bool is_tab(char c);
bool is_newline(char c);
bool is_eof(char c);

#endif
