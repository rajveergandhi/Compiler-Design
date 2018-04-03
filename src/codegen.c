#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "codegen.h"

// global variable for the codegen output file
extern FILE *codegen_file;

// global codegen indentation variable; it is incremented whenever necessary as required by the syntax of the target language (Python)
int c_indent = 0;

// function for indenting code
void codegenIndent(int indent_level) {
    // one level of indentation is defined as 4 spaces
    int indent_val = 4;
    for (int i = 0; i < indent_val * indent_level; ++i) {
        fprintf(codegen_file, " ");
    }
}

void codegenPROGRAM(PROGRAM *node) {
    codegenTOPLEVELDECL(node->topleveldecls);
    fprintf(codegen_file, "\nif __name__== \"__main__\":\n\tmain()");
}

void codegenTOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case dcl_toplevel:
                codegenDCL(i->val.dcl);
                break;
            case func_dcl_toplevel:
                codegenFUNCDCL(i->val.funcdcl);
                break;
        }
    }
}

void codegenDCL(DCL *node) {
    switch (node->kind) {
        case var:
            codegenVARDCL(node->val.vardcl);
            break;
        case type:
            codegenTYPEDCL(node->val.typedcl);
            break;
    }
}

void codegenVARDCL(VARDCL *node) {
    for (VARDCL *i = node; i; i = i->next) {
        if (i->exprlist) {
            codegenIDLIST(i->idlist);
            fprintf(codegen_file, " = ");
            codegenEXPRLIST(i->exprlist);
            fprintf(codegen_file, "\n");
        }
    }
}

void codegenTYPEDCL(TYPEDCL *node) {
}

void codegenFUNCDCL(FUNCDCL *node) {
    fprintf(codegen_file, "def %s", node->identifier);
    codegenFUNC_SIGNATURE(node->signature);
    c_indent++;
    codegenBLOCK(node->block);
    c_indent--;
}

void codegenFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    fprintf(codegen_file, "(");
    // for (PARAM_LIST *i = node->params; i; i = i->next) {
    //     codegenIDLIST(i->idlist);
    //     printf(" ");
    //     codegenTYPE(i->type);
    //     if (i->next)
    //         printf(", ");
    // }
    fprintf(codegen_file, "):\n");
    // if (node->type) {
    //     printf(" ");
    //     codegenTYPE(node->type);
    // }
}

void codegenBLOCK(BLOCK *node) {
    //codegenIndent(c_indent);
    // fprintf(codegen_file, "\n");
    codegenSTATEMENTS(node->stmts);
    // fprintf(codegen_file, "\n");
}

void codegenSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next) {
        codegenSTATEMENT(i->stmt);
    }
}

void codegenSTATEMENT(STATEMENT *node) {
    codegenIndent(c_indent);
    switch(node->kind) {
        case dcl_s:
            codegenDCL(node->val.dcl);
            break;
        case simple_s:
            codegenSIMPLE(node->val.simple);
            break;
        case return_stmt_s:
            // printf("return");
            // if (node->val.return_stmt) {
            //     printf(" ");
            //     prettyEXPR(node->val.return_stmt);
            // }
            // printf("\n");
            break;
        case break_stmt_s:
            // printf("break\n");
            break;
        case continue_stmt_s:
            // printf("continue\n");
            break;
        case block_s:
            codegenBLOCK(node->val.block);
            break;
        case if_stmt_s:
            if (node->val.if_stmt.simple) {
                codegenSIMPLE(node->val.if_stmt.simple);
                codegenIndent(c_indent);
            }
            fprintf(codegen_file, "if ");
            codegenEXPR(node->val.if_stmt.expr);
            fprintf(codegen_file, ":\n");
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    c_indent++;
                    codegenBLOCK(node->val.if_stmt.val.if_block);
                    c_indent--;
                    break;
                case else_if:
                    c_indent++;
                    codegenSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    c_indent--;
                    codegenELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    break;
            }
            break;
        case switch_stmt_s:
            // printf("switch ");
            // if (node->val.switch_stmt.condition->simple) {
            //     prettySIMPLE(node->val.switch_stmt.condition->simple);
            //     printf("; ");
            // }
            // if (node->val.switch_stmt.condition->expr) {
            //     prettyEXPR(node->val.switch_stmt.condition->expr);
            //     printf(" ");
            // }
            // if (node->val.switch_stmt.caselist)
            //     prettySWITCH_CASELIST(node->val.switch_stmt.caselist);
            break;
        case for_stmt_s:
            // printf("for ");
            // switch(node->val.for_stmt.condition->kind) {
            //     case infinite:
            //         break;
            //     case while_loop:
            //         prettyEXPR(node->val.for_stmt.condition->val.while_expr);
            //         break;
            //     case threepart:
            //         if (node->val.for_stmt.condition->val.threepart.init) {
            //             prettySIMPLE(node->val.for_stmt.condition->val.threepart.init);
            //             printf(" ");
            //         }
            //         if (node->val.for_stmt.condition->val.threepart.condition) {
            //             prettyEXPR(node->val.for_stmt.condition->val.threepart.condition);
            //             printf(";");
            //         }
            //         if (node->val.for_stmt.condition->val.threepart.post)
            //             prettySIMPLE(node->val.for_stmt.condition->val.threepart.post);
            //         break;
            // }
            // prettyBLOCK(node->val.for_stmt.block);
            break;
        case print_stmt_s:
            fprintf(codegen_file, "print ");
            codegenEXPRLIST(node->val.print);
            fprintf(codegen_file, ",\n");
            break;
        case println_stmt_s:
            fprintf(codegen_file, "print ");
            codegenEXPRLIST(node->val.print);
            fprintf(codegen_file, "\n");
            break;
    }
}

void codegenELSE_BLOCK(ELSE_BLOCK *node) {
    codegenIndent(c_indent);
    switch (node->kind) {
        case if_stmt_else:
            c_indent++;
            fprintf(codegen_file, "elif ");
            codegenEXPR(node->val.if_stmt->val.if_stmt.expr);
            fprintf(codegen_file, ":\n");
            c_indent--;
            switch (node->val.if_stmt->val.if_stmt.kind_else) {
                case no_else:
                    c_indent++;
                    codegenBLOCK(node->val.if_stmt->val.if_stmt.val.if_block);
                    c_indent--;
                    break;
                case else_if:
                    c_indent++;
                    codegenSTATEMENTS(node->val.if_stmt->val.if_stmt.val.else_block.stmts);
                    c_indent--;
                    codegenELSE_BLOCK(node->val.if_stmt->val.if_stmt.val.else_block.else_block);
                    break;
            }
            break;
        case block_else:
            c_indent++;
            fprintf(codegen_file, "else:\n");
            codegenBLOCK(node->val.block);
            c_indent--;
            break;
    }
}

void codegenSIMPLE(SIMPLE *node) {
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            codegenEXPR(node->val.expr);
            break;
        case increment_kind:
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "++");
            break;
        case decrement_kind:
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "--");
            break;
        case assignment_kind:
            codegenEXPRLIST(node->val.assignment.LHS_expr_list);
            fprintf(codegen_file, " %s ", node->val.assignment.assign_op);
            codegenEXPRLIST(node->val.assignment.RHS_expr_list);
            fprintf(codegen_file, "\n");
            break;
        case shortDcl_kind:
            codegenEXPRLIST(node->val.shortDcl.LHS_idlist);
            fprintf(codegen_file, " = ");
            codegenEXPRLIST(node->val.shortDcl.RHS_expr_list);
            fprintf(codegen_file, "\n");
            break;
    }
}

void codegenIDLIST(IDLIST *node) {
    for (IDLIST *i = node; i; i = i->next) {
        if (strcmp(i->id, "True") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_TRUE");
        }
        else if (strcmp(i->id, "False") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_FALSE");
        }
        else if (strcmp(i->id, "None") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_NONE");
        }
        else if (strcmp(i->id, "and") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_AND");
        }
        else if (strcmp(i->id, "or") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_OR");
        }
        else if (strcmp(i->id, "not") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_NOT");
        }
        else if (strcmp(i->id, "as") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_AS");
        }
        else if (strcmp(i->id, "assert") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_ASSERT");
        }
        else if (strcmp(i->id, "break") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_BREAK");
        }
        else if (strcmp(i->id, "continue") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_CONTINUE");
        }
        else if (strcmp(i->id, "class") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_CLASS");
        }
        else if (strcmp(i->id, "def") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_DEF");
        }
        else if (strcmp(i->id, "del") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_DEL");
        }
        else if (strcmp(i->id, "elif") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_ELIF");
        }
        else if (strcmp(i->id, "except") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_EXCEPT");
        }
        else if (strcmp(i->id, "raise") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_RAISE");
        }
        else if (strcmp(i->id, "try") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_TRY");
        }
        else if (strcmp(i->id, "finally") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_FINALLY");
        }
        else if (strcmp(i->id, "from") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_FROM");
        }
        else if (strcmp(i->id, "import") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_IMPORT");
        }
        else if (strcmp(i->id, "global") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_GLOBAL");
        }
        else if (strcmp(i->id, "in") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_IN");
        }
        else if (strcmp(i->id, "is") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_IS");
        }
        else if (strcmp(i->id, "lambda") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_LAMBDA");
        }
        else if (strcmp(i->id, "nonlocal") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_NONLOCAL");
        }
        else if (strcmp(i->id, "pass") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_PASS");
        }
        else if (strcmp(i->id, "with") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_WITH");
        }
        else if (strcmp(i->id, "yield") == 0 ) {
            fprintf(codegen_file, "$$_GOLITE_YIELD");
        }
        else {
            fprintf(codegen_file, "%s", i->id);
        }
        if (i->next) fprintf(codegen_file, ", ");
    }
}

void codegenEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next) {
        codegenEXPR(i->expr);
        if (i->next) fprintf(codegen_file, ", ");
    }
}

void codegenEXPR(EXPR *node) {
    switch (node->kind) {
        case expressionKindPlus:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " + ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindMinus:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " - ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindMult:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " * ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindDiv:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " / ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindMod:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " %% ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindLT:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " < ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindLT_EQ:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " <= ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindGT:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " > ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindGT_EQ:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " >= ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindEQ_EQ:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " == ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindNotEquals:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " != ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindShift_Right:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " >> ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindShift_Left:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " << ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindAnd:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " & ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindAMP_XOR:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " &^ ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindOr:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " | ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindXor:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " ^ ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindLogicalAnd:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " && ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindLogicalOr:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " || ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindPlusUnary:
            fprintf(codegen_file, "(+(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case expressionKindMinusUnary:
            fprintf(codegen_file, "(-(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case expressionKindNotUnary:
            fprintf(codegen_file, "(!(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case expressionKindXorUnary:
            fprintf(codegen_file, "(^(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case append_expr:
            fprintf(codegen_file, "append(%s, ", node->val.append_expr.identifier);
            codegenEXPR(node->val.append_expr.expr);
            fprintf(codegen_file, ")\n");
            break;
        case intval:
            fprintf(codegen_file, "%d", node->val.intLiteral);
            break;
        case floatval:
            fprintf(codegen_file, "%f", node->val.floatLiteral);
            break;
        case stringval:
            fprintf(codegen_file, "%s", node->val.stringLiteral);
            break;
        case rawstringval:
            fprintf(codegen_file, "%s", node->val.stringLiteral);
            break;
        case runeval:
            fprintf(codegen_file, "%s", node->val.runeLiteral);
            break;
        case other_expr_kind:
            codegenOTHER_EXPR(node->val.other_expr);
            break;
    }
}

void codegenOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            fprintf(codegen_file, "%s", node->val.identifier);
            break;
        case paren_kind:
            codegenEXPR(node->val.expr);
            break;
        case func_call_kind:
            // prettyOTHER_EXPR(node->val.func_call.id);
            // printf("(");
            // prettyEXPRLIST(node->val.func_call.args);
            // printf(")");
            break;
        case index_kind:
            // prettyOTHER_EXPR(node->val.index.expr);
            // printf("[");
            // prettyEXPR(node->val.index.index);
            // printf("]");
            break;
        case struct_access_kind:
            // prettyOTHER_EXPR(node->val.struct_access.expr);
            // printf(".%s", node->val.struct_access.identifier);
            break;
    }
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
