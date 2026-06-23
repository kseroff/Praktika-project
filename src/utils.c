#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen(void) {
    if (getenv("TERM")) {
        system("clear");
    }
    else {
        printf("\n\n\n\n\n");
    }
}

int checkForExtraChars(void) {
    int c = getchar();
    return (c != '\n' && c != EOF);
}
