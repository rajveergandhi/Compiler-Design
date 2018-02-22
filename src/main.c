#include <stdio.h>
#include <string.h>


int yylex();
void yyparse();
int g_tokens = 0; // global variable to turn on token output
int g_symbols = 0; // global variable to turn on symbol table output
extern FILE *yyin;
FILE *codegen_file;

int main(int argc, char* argv[])
{
    if (argc >= 2) {
        char* mode = argv[1];
        yyin = fopen(argv[2], "r");
        if(yyin != NULL) {
            if (strcmp(mode, "scan") == 0) {
                while (yylex()) {}
                printf("OK\n");
            }
            else if (strcmp(mode, "tokens") == 0) {
                g_tokens = 1;
                while (yylex()) {}
            }
            else if (strcmp(mode, "parse") == 0) {
                yyparse();
                printf("OK\n");
            }
        }
        else {
            printf("Error opening file: %s\n", argv[2]);
        }
    }
    else {
        printf("Error: incorrect number of arguments");
        return 1;
    }
    return 0;
}
