#define _CRT_SECURE_NO_WARNINGS

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

void clear_screen(void) {
    /* Do not use system("clear") or system("cls").
       Printing the same separator works consistently on Windows, Linux and macOS. */
    printf("\n----------------------------------------\n");
}

int read_line(char* buffer, size_t buffer_size) {
    size_t length;
    int ch;

    if (buffer == NULL || buffer_size == 0) {
        return 0;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    return 1;
}

int parse_int(const char* text, int* value) {
    char* endptr = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*text)) {
        text++;
    }

    if (*text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &endptr, 10);

    if (text == endptr || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int read_int_from_stdin(const char* prompt, int* value) {
    char line[256];

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (!read_line(line, sizeof(line))) {
        return 0;
    }

    return parse_int(line, value);
}

void wait_for_enter(void) {
    char line[8];
    (void)read_line(line, sizeof(line));
}
