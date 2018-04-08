#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codegen.h"
#include "symbol.h"
#include "type.h"

// global variable for the codegen output file
extern FILE *codegen_file;

// global codegen indentation variable; it is incremented whenever necessary as required by the syntax of the target language (Python)
int c_indent = 0;
int j = 0;

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
    for (VARDCL *i = node; i; i = i->next) {
        EXPRLIST *k = i->exprlist;
        for (IDLIST *j = node->idlist; j; j = j->next) {
            if (!i->type || i->type->kind != struct_type_kind) {
                codegenIndent(c_indent);
                fprintf(codegen_file, "__GOLITE__%s", j->id);
                fprintf(codegen_file, " = ");
            }
            if (k) {
                codegenEXPR(k->expr);
                k = k->next;
            }
            else {
                if (i->type->kind == struct_type_kind) {
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "class __GOLITE__%s__:\n", j->id);
                    c_indent++;
                    codegenTYPE(i->type);
                    c_indent--;
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "__GOLITE__%s = __GOLITE__%s__()\n", j->id, j->id);
                }
                else {
                    codegenTYPE(i->type);
                }
            }
            fprintf(codegen_file, "\n");
        }
    }
}

void codegenTYPE(TYPE *node) {
    switch (node->kind) {
        case basic_type_kind:
            if (strcmp(node->val.basic_type, "int")==0)
                fprintf(codegen_file, "0");
            else if (strcmp(node->val.basic_type, "float64")==0)
                fprintf(codegen_file, "0.0");
            else if (strcmp(node->val.basic_type, "string")==0)
                fprintf(codegen_file, "\"\"");
            else if (strcmp(node->val.basic_type, "rune")==0)
                fprintf(codegen_file, "\"\"");
            else if (strcmp(node->val.basic_type, "bool")==0)
                fprintf(codegen_file, "False");
            else
                fprintf(codegen_file, "__GOLITE__%s", node->val.basic_type);
            break;
        case slice_type_kind:
            fprintf(codegen_file, "[");
            fprintf(codegen_file, "]");
            break;
        case array_type_kind:
            fprintf(codegen_file, "[");
            codegenTYPE(node->val.array_type.type);
            fprintf(codegen_file, "]");
            fprintf(codegen_file, " * %d", node->val.array_type.size);
            break;
        case struct_type_kind:
            {
                for (STRUCT_TYPE *i = node->val.struct_type; i; i = i->next) {
                    for (IDLIST *j = i->idlist; j; j = j->next) {
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "__GOLITE__%s", j->id);
                        fprintf(codegen_file, " = ");
                        codegenTYPE(node->val.struct_type->type);
                        fprintf(codegen_file, "\n");
                    }
                }
                if (!node->val.struct_type) {
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "pass\n");
                }
            }
            break;
    }
}

void codegenTYPEDCL(TYPEDCL *node) {
    for (TYPEDCL *i = node; i; i = i->next) {
        switch (node->type->kind) {
            case basic_type_kind:
            case slice_type_kind:
            case array_type_kind:
                // because Python is dynamically typed, we don't need to explicitly do anything
                break;
            case struct_type_kind:
                codegenIndent(c_indent);
                fprintf(codegen_file, "class __GOLITE__%s:\n", i->identifier);
                c_indent++;
                codegenTYPE(i->type);
                c_indent--;
                fprintf(codegen_file, "\n");
                break;
        }
    }
}

void codegenFUNCDCL(FUNCDCL *node) {
    if (strcmp(node->identifier, "main") == 0)
        fprintf(codegen_file, "def %s", node->identifier);
    else
        fprintf(codegen_file, "def __GOLITE__%s", node->identifier);
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
    // Python requires that to be syntactically correct, there be at least one statement in a block
    if (!node->stmts) {
        codegenIndent(c_indent);
        fprintf(codegen_file, "pass\n");
    }
    else
        codegenSTATEMENTS(node->stmts);
}

void codegenSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next) {
        codegenSTATEMENT(i->stmt);
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
                    fprintf(codegen_file, "\n");
                    c_indent--;
                    break;
                case else_if:
                    c_indent++;
                    if (!node->val.if_stmt.val.else_block.stmts) {
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "pass\n");
                    }
                    else
                        codegenSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    c_indent--;
                    codegenELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    fprintf(codegen_file, "\n");
                    break;
            }
            break;
        case switch_stmt_s:
            j = 0;
            if (node->val.switch_stmt.condition->simple)
                codegenSIMPLE(node->val.switch_stmt.condition->simple);
            codegenIndent(c_indent);
            if (node->val.switch_stmt.condition->expr) {
                fprintf(codegen_file, "if ");
                codegenEXPR(node->val.switch_stmt.condition->expr);
                fprintf(codegen_file, " == ");
            }
            else
                fprintf(codegen_file, "if ");
            if (node->val.switch_stmt.caselist) {
                for (SWITCH_CASELIST *i = node->val.switch_stmt.caselist; i; i=i->next) {
                    if (i->default_case) {
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "else:\n");
                    }
                    else {
                        if (j!=0) {
                            codegenIndent(c_indent);
                            fprintf(codegen_file, "elif ");
                            codegenEXPR(node->val.switch_stmt.condition->expr);
                            fprintf(codegen_file, " == ");
                        }
                        //codegenEXPRLIST(i->exprlist);
                        for (EXPRLIST *k = i->exprlist; k; k = k->next) {
                            codegenEXPR(k->expr);
                            if (k->next) {
                                fprintf(codegen_file, " or ");
                                codegenEXPR(node->val.switch_stmt.condition->expr);
                                fprintf(codegen_file, " == ");
                            }
                        }
                        fprintf(codegen_file, ":\n");
                        j++;
                    }
                    if (i->statements) {
                        codegenIndent(c_indent);
                        codegenSTATEMENTS(i->statements);
                    }
                    else {
                        c_indent++;
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "pass\n");
                        c_indent--;
                    }
                }
            }
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
                    codegenBLOCK(node->val.for_stmt.block);
                    c_indent--;
                    fprintf(codegen_file, "\n");
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init)
                        codegenSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "while ");
                    node->val.for_stmt.condition->val.threepart.condition ? codegenEXPR(node->val.for_stmt.condition->val.threepart.condition) : fprintf(codegen_file, "True");
                    fprintf(codegen_file, ":\n");
                    c_indent++;

                    // if post expression exists, then either insert it at the end of BLOCK, or immediately preceding the first encountered "continue" statement in the block
                    if (node->val.for_stmt.condition->val.threepart.post) {
                        for (STATEMENTS *i = node->val.for_stmt.block->stmts; i; i = i->next) {
                            // case 1: continue statement is the first statement
                            if (i->stmt->kind == continue_stmt_s) {
                                STATEMENTS *post_stmt = makeSTATEMENTS(makeSTATEMENT_simple(node->val.for_stmt.condition->val.threepart.post), i);
                                node->val.for_stmt.block->stmts = post_stmt;
                                break;
                            }
                            // case 2: continue statement exists but is not the first statement
                            else if (i->next && i->next->stmt->kind == continue_stmt_s) {
                                STATEMENTS *post_stmt = makeSTATEMENTS(makeSTATEMENT_simple(node->val.for_stmt.condition->val.threepart.post), i->next);
                                i->next = post_stmt;
                                break;
                            }
                            // case 3: continue statement does not exist but there is at least one statement
                            else if (!(i->next)) {
                                STATEMENTS *post_stmt = makeSTATEMENTS(makeSTATEMENT_simple(node->val.for_stmt.condition->val.threepart.post), NULL);
                                i->next = post_stmt;
                                break;
                            }
                        }
                        // case 4: no statements in loop
                        if (!(node->val.for_stmt.block->stmts)) {
                            STATEMENTS *post_stmt = makeSTATEMENTS(makeSTATEMENT_simple(node->val.for_stmt.condition->val.threepart.post), NULL);
                            node->val.for_stmt.block->stmts = post_stmt;
                        }
                    }

                    codegenBLOCK(node->val.for_stmt.block);
                    c_indent--;
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
    fprintf(codegen_file, "else:\n");
    switch (node->kind) {
        case if_stmt_else:
            c_indent++;
            codegenSTATEMENT(node->val.if_stmt);
            c_indent--;
            break;
        case block_else:
            c_indent++;
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
            if (strcmp(node->val.assignment.assign_op, "&^=")==0)
                fprintf(codegen_file, " &= ~");
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
        fprintf(codegen_file, "__GOLITE__%s", i->id);
        if (i->next)
            fprintf(codegen_file, ", ");
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
            fprintf(codegen_file, "__GOLITE__%s + [", node->val.append_expr.identifier);
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
            if (strcmp(node->val.identifier, "true")==0)
                fprintf(codegen_file, "True");
            else if (strcmp(node->val.identifier, "false")==0)
                fprintf(codegen_file, "False");
            else
                fprintf(codegen_file, "__GOLITE__%s", node->val.identifier);
            break;
        case paren_kind:
            codegenEXPR(node->val.expr);
            break;
        case func_call_kind:
            if (isFunction(node->val.func_call.id->data)) {
                codegenOTHER_EXPR(node->val.func_call.id);
                fprintf(codegen_file, "(");
                codegenEXPRLIST(node->val.func_call.args);
                fprintf(codegen_file, ")");
            }
            else { // cast: simply remove the function call since we can only have one argument and Python is dynamically typed
                codegenEXPR(node->val.func_call.args->expr);
            }
            break;
        case index_kind:
            codegenOTHER_EXPR(node->val.index.expr);
            fprintf(codegen_file, "[");
            codegenEXPR(node->val.index.index);
            fprintf(codegen_file, "]");
            break;
        case struct_access_kind:
            codegenOTHER_EXPR(node->val.struct_access.expr);
            fprintf(codegen_file, ".%s", node->val.struct_access.identifier);
            break;
    }
}
