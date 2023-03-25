#ifndef AIDS
#define AIDS
#include <stddef.h>
#include <stdbool.h>

void read_file(char *path, char **data);

size_t str_skip_while(char **str, bool (*predicate)(char));
size_t str_count_if(char *str, bool (*predicate)(char));

bool is_whitespace(char c);
bool is_space(char c);
bool is_tab(char c);
bool is_newline(char c);
bool is_eof(char c);

#endif
