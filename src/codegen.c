#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "codegen.h"

// global variable for the codegen output file
extern FILE *codegen_file;

// global codegen indentation variable; it is incremented whenever necessary as required by the syntax of the target language (Python)
int c_indent = 0;

// function for indenting code
void codegenPrettyIndent(int indent_level) {
    // one level of indentation is defined as 4 spaces
    int indent_val = 4; 
    for (int i = 0; i < indent_val * indent_level; ++i) {
        fprintf(codegen_file, " ");
    }
}

void codegenPROGRAM(PROGRAM *node) {
    //fprintf(codegen_file, "print \"foobar\"\n");
}




    /*
    switch (node->kind) {
        case k_program:
            // include all libraries necessary
            fprintf(codegen_file, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdbool.h>\n\n");

            // create a local string concatenation function so that we can also add two string literals
            fprintf(codegen_file, "char *strcat_local(char *str1, const char *str2) {\n" \
                            "    size_t len1 = strlen(str1);\n" \
                            "    size_t len2 = strlen(str2);\n" \
                            "    char *result = (char*)malloc(len1 + len2 + 1);\n" \
                            "    size_t i, j;\n"
                            "    for (i = 0; str1[i] != '\\0'; ++i)\n" \
                            "        result[i] = str1[i];\n" \
                            "    for (j = 0; str2[j] != '\\0'; j++)\n" \
                            "        result[i+j] = str2[j];\n" \
                            "    result[i+j] = '\\0';\n" \
                            "    return result;\n" \
                            "}\n\n");

            // function for multiplying a string to an int; semantics are repetition
            fprintf(codegen_file, "char *str_mult(const char *str, int num) {\n" \
                            "    if (num < 0) {\n"
                            "        fprintf(stderr, \"Error: string multiplication by a negative number\\n\");\n"
                            "        exit(1);\n" \
                            "    }\n" \
                            "    size_t len = strlen(str);\n" \
                            "    char *result = (char*)malloc(len * num + 1);\n" \
                            "    for(int i = 0; i < num; ++i)\n" \
                            "        strcpy(result + len * i, str);\n" \
                            "    return result;\n" \
                            "}\n\n");

            // function for reading a bool as a string: "TRUE" or "FALSE" or runtime error
            fprintf(codegen_file, "bool read_bool() {\n" \
                            "    char bool_string[1024];\n" \
                            "    scanf(\"%%s\", bool_string);\n" \
                            "    if (strcmp(bool_string, \"TRUE\") == 0)\n" \
                            "        return true;\n" \
                            "    else if (strcmp(bool_string, \"FALSE\") == 0)\n" \
                            "        return false;\n" \
                            "    else {\n" \
                            "        fprintf(stderr, \"Error: invalid boolean string input. Must be 'TRUE' or 'FALSE'\\n\");\n" \
                            "        exit(1);\n" \
                            "    }\n" \
                            "}\n\n");

            fprintf(codegen_file, "int main() {\n");
            c_indent++;
            if (node->val.program.dcls)
                codegen(node->val.program.dcls);
            fprintf(codegen_file, "\n");
            if (node->val.program.stmts)
                codegen(node->val.program.stmts);
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "return 0;\n");
            c_indent--;
            fprintf(codegen_file, "}\n");
            break;
        case k_dcl:
            for (NODE *i = node; i != NULL; i = i->val.dcl.nextDcl) {
                codegenPrettyIndent(c_indent);
                if (strcmp(i->val.dcl.type, "string") == 0) {
                    fprintf(codegen_file, "char %s[1024] = ", i->val.dcl.identifier);
                }
                else {
                    if (strcmp(i->val.dcl.type, "boolean") == 0) i->val.dcl.type = "bool";
                    fprintf(codegen_file, "%s %s = ", i->val.dcl.type, i->val.dcl.identifier);
                }
                codegen(i->val.dcl.expr);
                fprintf(codegen_file, ";\n");
            }
            break;
        case k_statementKindRead:
            codegenPrettyIndent(c_indent);
            switch (node->s_kind) {
                case s_int:
                    fprintf(codegen_file, "scanf(\"%%d\", &%s);\n", node->val.stmt.type.stmtRead);
                    break;
                case s_bool:
                    fprintf(codegen_file, "%s = read_bool();\n", node->val.stmt.type.stmtRead);
                    break;
                case s_float:
                    fprintf(codegen_file, "scanf(\"%%f\", &%s);\n", node->val.stmt.type.stmtRead);
                    break;
                case s_string:
                    fprintf(codegen_file, "scanf(\"%%s\", %s);\n", node->val.stmt.type.stmtRead);
                    break;
            }
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_statementKindPrint:
            codegenPrettyIndent(c_indent);
            if (node->val.stmt.type.stmtPrint->s_kind == s_bool) {
                fprintf(codegen_file, "printf(\"%%s\", ");
                codegen(node->val.stmt.type.stmtPrint);
                fprintf(codegen_file, "? \"TRUE\\n\": \"FALSE\\n\");\n");
            }
            else {
                switch (node->val.stmt.type.stmtPrint->s_kind) {
                    case s_int:
                        fprintf(codegen_file, "printf(\"%%d\\n\", ");
                        break;
                    case s_float:
                        fprintf(codegen_file, "printf(\"%%f\\n\", ");
                        break;
                    case s_string:
                        fprintf(codegen_file, "printf(\"%%s\\n\", ");
                        break;
                }
                codegen(node->val.stmt.type.stmtPrint);
                fprintf(codegen_file, ");\n");
            }
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_statementKindAssignment:
            codegenPrettyIndent(c_indent);
            if (node->val.stmt.type.stmtAssign.expr->s_kind == s_string) {
                fprintf(codegen_file, "strcpy(%s, ", node->val.stmt.type.stmtAssign.identifier);
                codegen(node->val.stmt.type.stmtAssign.expr);
                fprintf(codegen_file, ");\n");
            }
            else {
                fprintf(codegen_file, "%s = ", node->val.stmt.type.stmtAssign.identifier);
                codegen(node->val.stmt.type.stmtAssign.expr);
                fprintf(codegen_file, ";\n");
            }
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_statementKindWhile:
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "while (");
            codegen(node->val.stmt.type.stmtWhile.expr);
            fprintf(codegen_file, ") {\n");
            c_indent++;
            if (node->val.stmt.type.stmtWhile.stmts)
                codegen(node->val.stmt.type.stmtWhile.stmts);
            c_indent--;
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "}\n");
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_statementKindIfStmt:
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "if (");
            codegen(node->val.stmt.type.stmtIf.expr);
            fprintf(codegen_file, ") {\n");
            c_indent++;
            if (node->val.stmt.type.stmtIf.stmts)
                codegen(node->val.stmt.type.stmtIf.stmts);
            c_indent--;
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "}\n");
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_statementKindIfElseStmt:
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "if (");
            codegen(node->val.stmt.type.stmtIfElse.expr);
            fprintf(codegen_file, ") {\n");
            c_indent++;
            if (node->val.stmt.type.stmtIfElse.ifStmts)
                codegen(node->val.stmt.type.stmtIfElse.ifStmts);
            c_indent--;
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "} else {\n");
            c_indent++;
            if (node->val.stmt.type.stmtIfElse.elseStmts)
                codegen(node->val.stmt.type.stmtIfElse.elseStmts);
            c_indent--;
            codegenPrettyIndent(c_indent);
            fprintf(codegen_file, "}\n");
            if (node->val.stmt.nextStmt)
                codegen(node->val.stmt.nextStmt);
            break;
        case k_expressionKindIdentifier:
            fprintf(codegen_file, "%s", node->val.identifier);
            break;
        case k_expressionKindIntLiteral:
            fprintf(codegen_file, "%d", node->val.intLiteral);
            break;
        case k_expressionKindFloatLiteral:
            fprintf(codegen_file, "%f", node->val.floatLiteral);
            break;
        case k_expressionKindBoolLiteral:
            fprintf(codegen_file, "%d", node->val.boolLiteral);
            break;
        case k_expressionKindStringLiteral:
            fprintf(codegen_file, "%s", node->val.stringLiteral);
            break;
        case k_expressionKindAddition:
            if ((node->val.exp_binary.lhs->s_kind == s_string) && (node->val.exp_binary.rhs->s_kind == s_string)) {
                fprintf(codegen_file, "strcat_local(");
                codegen(node->val.exp_binary.lhs);
                fprintf(codegen_file, ", ");
                codegen(node->val.exp_binary.rhs);
                fprintf(codegen_file, ")");
            }
            else {
                fprintf(codegen_file, "(");
                codegen(node->val.exp_binary.lhs);
                fprintf(codegen_file, " + ");
                codegen(node->val.exp_binary.rhs);
                fprintf(codegen_file, ")");
            }
            break;
        case k_expressionKindSubtraction:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " - ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindMultiplication:
            if ((node->val.exp_binary.lhs->s_kind == s_string) && (node->val.exp_binary.rhs->s_kind == s_int)) {
                fprintf(codegen_file, "str_mult(");
                codegen(node->val.exp_binary.lhs);
                fprintf(codegen_file, ", ");
                codegen(node->val.exp_binary.rhs);
                fprintf(codegen_file, ")");
            }
            else if ((node->val.exp_binary.lhs->s_kind == s_int) && (node->val.exp_binary.rhs->s_kind == s_string)) {
                fprintf(codegen_file, "str_mult(");
                codegen(node->val.exp_binary.rhs);
                fprintf(codegen_file, ", ");
                codegen(node->val.exp_binary.lhs);
                fprintf(codegen_file, ")");
            }
            else {
                fprintf(codegen_file, "(");
                codegen(node->val.exp_binary.lhs);
                fprintf(codegen_file, " * ");
                codegen(node->val.exp_binary.rhs);
                fprintf(codegen_file, ")");
            }
            break;
        case k_expressionKindDivision:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " / ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindEqualsEquals:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " == ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindNotEquals:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " != ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindLogicalAnd:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " && ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindLogicalOr:
            fprintf(codegen_file, "(");
            codegen(node->val.exp_binary.lhs);
            fprintf(codegen_file, " || ");
            codegen(node->val.exp_binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindNot:
            fprintf(codegen_file, "!(");
            codegen(node->val.exp_unary);
            fprintf(codegen_file, ")");
            break;
        case k_expressionKindUnaryMinus:
            fprintf(codegen_file, "-(");
            codegen(node->val.exp_unary);
            fprintf(codegen_file, ")");
            break;
    }
}
*/
