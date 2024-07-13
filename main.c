// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interactive.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        start_interactive();
        exit(EXIT_SUCCESS);
    }

    char* input = argv[1];
    FILE* input_file = fopen(input, "r");

    if (!input_file) {
        fprintf(stderr, "Error: File \"%s\" doesn't exist\n", input);
        exit(EXIT_FAILURE);
    }

    // Get size of file
    fseek(input_file, 0L, SEEK_END);
    int code_len = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);

    char* code_buffer = malloc(code_len);

    fread(code_buffer, sizeof(char), code_len, input_file);
    fclose(input_file);

    run_code(code_buffer, code_len);

    free(code_buffer);
    return 0;
}

void run_code(char* code, int code_len)
{
    // Create cell array and set every cell to 0
    char cells[CELL_COUNT];
    memset(cells, 0, sizeof(cells));
    
    int cell_i = 0; // current cell index
    int b = 0; // bracket counter
    
    // Start interpreting code
    for (int i = 0; i < code_len; i++) {
        switch (code[i]) {
            case '>': cell_i++; break;
            case '<': cell_i--; break;
            case '+': cells[cell_i]++; break;
            case '-': cells[cell_i]--; break;
            case '.': putchar(cells[cell_i]); break;
            case ',':
                      cells[cell_i] = getchar();
                      getchar(); // remove '\n' from stdin
                      break;
            case '[':
                      if (cells[cell_i] != 0) continue;
                      b++;
                      
                      while (b > 0) {
                          switch (code[i]) {
                              case '[': b++; break;
                              case ']': b--; break;
                          }

                          // In case if matching brace wasnt found and we
                          // got past the code_len
                          if (++i > code_len) {
                              break;
                          }
                      } 
                      break;
            case ']':
                      if (cells[cell_i] == 0) continue;
                      b++;
                      
                      while (b > 0) {
                          switch (code[i]) {
                              case ']': b++; break;
                              case '[': b--; break;
                          }

                          if (--i < 0) {
                              break;
                          }
                      } 
                      break;
            default:
                      break;
        }
    }
}

