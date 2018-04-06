#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codegen.h"
#include "symbol.h"

// global variable for the codegen output file
extern FILE *codegen_file;

// global codegen indentation variable; it is incremented whenever necessary as required by the syntax of the target language (Python)
int c_indent = 0;
int insideFor = 0;
int continueInsideFor = 0;

// function for indenting code
void codegenIndent(int indent_level) {
    // one level of indentation is defined as 4 spaces
    int indent_val = 4;
    for (int i = 0; i < indent_val * indent_level; ++i) {
        fprintf(codegen_file, " ");
    }
}

void codegenPROGRAM(PROGRAM *node) {
    // import necessary python libraries
    fprintf(codegen_file, "# import all necessary Python libraries\n");
    fprintf(codegen_file, "from __future__ import print_function\n\n");

    // TODO: define all user-defined functions we need
    codegenTOPLEVELDECL(node->topleveldecls);

    // if symbol table has a function called main, then have it run automatically
    SYMBOL *s = getSymbol_no_error(node->symboltable, "main");
    if (s && s->data->valKind == func_signature_type)
        fprintf(codegen_file, "\nif __name__ == \"__main__\":\n    main()");
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
    // TODO: initialization for uninitialized variables
    for (VARDCL *i = node; i; i = i->next) {
        if (i->exprlist) {
            codegenIndent(c_indent);
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
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        codegenIDLIST(i->idlist);
        if (i->next)
            printf(", ");
    }
    fprintf(codegen_file, "):\n");
}

void codegenBLOCK(BLOCK *node) {
    // TODO: see how to implement scoping; we can also do an "if true"
    codegenSTATEMENTS(node->stmts);

    // Python requires that to be syntactically correct, there be at least one statement in a block
    if (!node->stmts) {
        codegenIndent(c_indent);
        fprintf(codegen_file, "pass\n");
    }
}

void codegenSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next) {
        codegenSTATEMENT(i->stmt);
        if (continueInsideFor)
            return;
    }
}

void codegenSTATEMENT(STATEMENT *node) {
    switch(node->kind) {
        case dcl_s:
            codegenDCL(node->val.dcl);
            break;
        case simple_s:
            codegenSIMPLE(node->val.simple);
            break;
        case return_stmt_s:
            codegenIndent(c_indent);
            fprintf(codegen_file, "return");
            if (node->val.return_stmt) {
                fprintf(codegen_file, " ");
                codegenEXPR(node->val.return_stmt);
            }
            fprintf(codegen_file, "\n");
            break;
        case break_stmt_s:
            codegenIndent(c_indent);
            fprintf(codegen_file, "break\n");
            break;
        case continue_stmt_s:
            if (insideFor) {
                continueInsideFor = 1;
                return;
            }
            codegenIndent(c_indent);
            fprintf(codegen_file, "continue\n");
            break;
        case block_s:
            codegenBLOCK(node->val.block);
            break;
        case if_stmt_s:
            if (node->val.if_stmt.simple)
                codegenSIMPLE(node->val.if_stmt.simple);
            codegenIndent(c_indent);
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
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "while True:\n");
                    c_indent++;
                    codegenBLOCK(node->val.for_stmt.block);
                    c_indent--;
                    fprintf(codegen_file, "\n");
                    break;
                case while_loop:
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "while ");
                    codegenEXPR(node->val.for_stmt.condition->val.while_expr);
                    fprintf(codegen_file, ":\n");
                    c_indent++;
                    if (insideFor) {
                        insideFor = 0;
                    }
                    codegenBLOCK(node->val.for_stmt.block);
                    c_indent--;
                    fprintf(codegen_file, "\n");
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init) {
                        codegenSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    }
                    if (node->val.for_stmt.condition->val.threepart.condition) {
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "while ");
                        codegenEXPR(node->val.for_stmt.condition->val.threepart.condition);
                        fprintf(codegen_file, ":\n");
                        c_indent++;
                        if (node->val.for_stmt.condition->val.threepart.post) {
                            insideFor = 1;
                        }
                        else
                            insideFor = 0;
                        codegenBLOCK(node->val.for_stmt.block);
                        c_indent--;
                    }
                    else {
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "while True:\n");
                        c_indent++;
                        if (node->val.for_stmt.condition->val.threepart.post) {
                            insideFor = 1;
                        }
                        else
                            insideFor = 0;
                        codegenBLOCK(node->val.for_stmt.block);
                        c_indent--;
                        fprintf(codegen_file, "\n");
                    }
                    // codegenIndent(c_indent);
                    // codegenBLOCK(node->val.for_stmt.block);
                    if (node->val.for_stmt.condition->val.threepart.post) {
                        c_indent++;
                        codegenSIMPLE(node->val.for_stmt.condition->val.threepart.post);
                        if (continueInsideFor) {
                            codegenIndent(c_indent);
                            fprintf(codegen_file, "continue\n");
                            continueInsideFor = 0;
                        }
                        c_indent--;
                        fprintf(codegen_file, "\n");
                    }
                    break;
            }
            break;
        case print_stmt_s:
            codegenIndent(c_indent);
            fprintf(codegen_file, "print(");
            codegenEXPRLIST(node->val.print);
            if (node->val.print)
                fprintf(codegen_file, ", ");
            fprintf(codegen_file, " sep='', end='')\n");
            break;
        case println_stmt_s:
            codegenIndent(c_indent);
            fprintf(codegen_file, "print(");
            codegenEXPRLIST(node->val.print);
            if (node->val.print)
                fprintf(codegen_file, ", ");
            fprintf(codegen_file, " sep=' ', end='\\n')\n");
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
            codegenIndent(c_indent);
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "+= 1\n");
            break;
        case decrement_kind:
            codegenIndent(c_indent);
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "-= 1\n");
            break;
        case assignment_kind:
            codegenIndent(c_indent);
            codegenEXPRLIST(node->val.assignment.LHS_expr_list);
            if ((strcmp(node->val.assignment.assign_op), "&^=")==0)
                fprintf(codegen_file, " &= ~", node->val.assignment.assign_op);
            else
                fprintf(codegen_file, " %s ", node->val.assignment.assign_op);
            codegenEXPRLIST(node->val.assignment.RHS_expr_list);
            fprintf(codegen_file, "\n");
            break;
        case shortDcl_kind:
            codegenIndent(c_indent);
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
            fprintf(codegen_file, " & ~");
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
            fprintf(codegen_file, " and ");
            codegenEXPR(node->val.binary.rhs);
            fprintf(codegen_file, ")");
            break;
        case expressionKindLogicalOr:
            fprintf(codegen_file, "(");
            codegenEXPR(node->val.binary.lhs);
            fprintf(codegen_file, " or ");
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
            fprintf(codegen_file, "(not(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case expressionKindXorUnary:
            fprintf(codegen_file, "(~(");
            codegenEXPR(node->val.expr_unary);
            fprintf(codegen_file, "))");
            break;
        case append_expr:
            fprintf(codegen_file, "%s + [", node->val.append_expr.identifier);
            codegenEXPR(node->val.append_expr.expr);
            fprintf(codegen_file, "]");
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
            {
                // convert to a raw string in Python
                char *raw = malloc(strlen(node->val.stringLiteral) + 2*sizeof(char));
                raw[0] = 'r';
                raw[1] = '"';
                strcpy(raw + 2, node->val.stringLiteral + 1);
                raw[strlen(raw)-1] = '"';
                raw[strlen(raw)] = '\0';

                fprintf(codegen_file, "%s", raw);
            }
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
            // TODO: getsymbol on node->val.identifier; if it is true/false and type is bool then print "True" or "False"
            fprintf(codegen_file, "%s", node->val.identifier);
            break;
        case paren_kind:
            codegenEXPR(node->val.expr);
            break;
        case func_call_kind:
            codegenIndent(c_indent);
            codegenOTHER_EXPR(node->val.func_call.id);
            fprintf(codegen_file, "(");
            codegenEXPRLIST(node->val.func_call.args);
            fprintf(codegen_file, ")");
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
