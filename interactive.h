// interative.h

#include <stdio.h>

#define CELL_COUNT 30000
#define START_BUFFER_SIZE 2048

char* read_code();
void run_code(char* code, int code_len);
void start_interactive();
