#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void clear_screen(void);
int read_line(char* buffer, size_t buffer_size);
int parse_int(const char* text, int* value);
int read_int_from_stdin(const char* prompt, int* value);
void wait_for_enter(void);

#endif // UTILS_H
