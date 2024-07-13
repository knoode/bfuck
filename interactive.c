// interactive.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "interactive.h"

void start_interactive()
{
    char* code = NULL;
    _Bool exit = false;

    printf("Type 'q' to quit from interactive mode\n");

    while (!exit) {
        printf(">>> ");

        code = read_code();
        size_t code_len = strlen(code);

        if (code[0] == 'q') {
            exit = true;
        } else {
            run_code(code, code_len);
            printf("\n");
        }

        free(code);
    }
}

char* read_code()
{
    char* code_buffer = NULL;
    size_t buf_size;

    if (getline(&code_buffer, &buf_size, stdin) == -1) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("Error: Cannot getline()");
            exit(EXIT_FAILURE);
        } 
    }

    return code_buffer;
}

