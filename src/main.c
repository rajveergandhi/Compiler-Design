#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "pretty.h"
#include "symbol.h"
/*
#include "type.h"
#include "codegen.h"
*/

void yyparse();
int yylex();
int g_tokens = 0;
int g_symbols = 0;
extern FILE *yyin;
PROGRAM *root;
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
                weedPROGRAM(root);
                printf("OK\n");
            }
            else if (strcmp(mode, "pretty") == 0) {
                yyparse();
                weedPROGRAM(root);
                prettyPROGRAM(root);
            }
            else if (strcmp(mode, "symbol") == 0) {
                yyparse();
                weedPROGRAM(root);
                g_symbols = 1;
                symPROGRAM(root);
            }
            /*
            else if (strcmp(mode, "typecheck") == 0) {
                yyparse();
                SymbolTable *t = initSymbolTable();
                symPROGRAM(t, root);
                typeImplementationPROGRAM(t, root);
                printf("OK\n");
            }
            else if (strcmp(mode, "codegen") == 0) {
                yyparse();
                SymbolTable *t = initSymbolTable();
                symPROGRAM(t, root);
                typeImplementationPROGRAM(t, root);

                // create the new filepath for the codegen output file
                char *codegen_filepath = strdup(argv[2]);
                int i;
                for (i = strlen(codegen_filepath)-1; codegen_filepath[i] != '.'; --i);
                codegen_filepath[i+1] = 'c';
                codegen_filepath[i+2] = '\0';
                codegen_file = fopen(codegen_filepath, "w");

                codegen(root);
                printf("OK\n");
            }
            */
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
