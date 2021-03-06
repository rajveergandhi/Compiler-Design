#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codegen.h"
#include "symbol.h"
#include "type.h"
#include <math.h>
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
    fprintf(codegen_file, "from __future__ import print_function\n");
    fprintf(codegen_file, "import copy\n");
    fprintf(codegen_file, "\n");

    codegenTOPLEVELDECL(node->topleveldecls);

    // if symbol table has a function called main, then have it run automatically
    SYMBOL *s = getSymbol_no_error(node->symboltable, "main");
    if (s && s->data->valKind == func_signature_type)
        fprintf(codegen_file, "if __name__ == \"__main__\":\n    main()");
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
                fprintf(codegen_file, "_GOLITE__%s", j->id);
                fprintf(codegen_file, " = ");
            }
            if (k) {
                //codegenEXPR(k->expr);
                //fprintf(codegen_file, "copy.deepcopy(");
                codegenEXPR(k->expr);
                //fprintf(codegen_file, ")");
                //if (k->next) fprintf(codegen_file, ", ");
                k = k->next;
            }
            else {
                if (i->type->kind == struct_type_kind) {
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "class _GOLITE__%s__:\n", j->id);
                    c_indent++;
                    codegenTYPE(i->type);
                    c_indent--;
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "_GOLITE__%s = _GOLITE__%s__()\n", j->id, j->id);
                }
                else if (i->type->kind == basic_type_kind && getSymbol_no_error(i->symboltable, i->type->val.basic_type)->data->val.type->kind == struct_type_kind) {
                    fprintf(codegen_file, "_GOLITE__%s()", i->type->val.basic_type);
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
                fprintf(codegen_file, "\"0\"");
            else if (strcmp(node->val.basic_type, "bool")==0)
                fprintf(codegen_file, "False");
            else
                fprintf(codegen_file, "_GOLITE__%s", node->val.basic_type);
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
                        fprintf(codegen_file, "_GOLITE__%s", j->id);
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
                fprintf(codegen_file, "class _GOLITE__%s:\n", i->identifier);
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
        fprintf(codegen_file, "def _GOLITE__%s", node->identifier);
    codegenFUNC_SIGNATURE(node->signature);
    c_indent++;

    for (int i=0; i < HashSize; i++) {
        for (SYMBOL *s = node->symboltable->table[i]; s; s=s->next) {
            if (s->data->category == variable_category) {
                codegenIndent(c_indent);
                fprintf(codegen_file, "global _GOLITE__%s\n", node->symboltable->table[i]->name);
            }
        }
    }

    codegenBLOCK(node->block);
    fprintf(codegen_file, "\n");
    c_indent--;
}

void codegenFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    int count = 0;
    fprintf(codegen_file, "(");
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        for (IDLIST *j = i->idlist; j; j = j->next) {
            if (strcmp(j->id, "_") == 0)
                fprintf(codegen_file, "__unused_%d", count++);
            else
                fprintf(codegen_file, "_GOLITE__%s", j->id);
            if (j->next)
                fprintf(codegen_file, ", ");
        }
        if (i->next)
            fprintf(codegen_file, ", ");
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
                DataType *res = resolveType(node->val.return_stmt->data, node->symboltable, 1);
                if (res->val.type->kind == slice_type_kind || res->val.type->kind == array_type_kind || res->val.type->kind == struct_type_kind) {
                    fprintf(codegen_file, "copy.deepcopy(");
                    codegenEXPR(node->val.return_stmt);
                    fprintf(codegen_file, ")");
                }
                else {
                    codegenEXPR(node->val.return_stmt);
                }
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
                if (node->val.switch_stmt.condition->expr->val.other_expr->kind == func_call_kind) {
                    fprintf(codegen_file, "_GOLITE__switchFuncCall = ");
                    if (isFunction(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.id->data)) {
                        //codegenIndent(c_indent);
                        codegenOTHER_EXPR(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.id);
                        fprintf(codegen_file, "(");
                        codegenEXPRLIST(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.args);
                        fprintf(codegen_file, ")\n");
                        codegenIndent(c_indent);
                        fprintf(codegen_file, "if _GOLITE__switchFuncCall == ");
                    }
                    else { // cast: simply remove the function call since we can only have one argument and Python is dynamically typed
                        codegenEXPR(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.args->expr);
                    }
                    //fprintf(codegen_file, " == ");
                }
                else {
                    fprintf(codegen_file, "if ");
                    codegenEXPR(node->val.switch_stmt.condition->expr);
                    fprintf(codegen_file, " == ");
                }
            }
            else
                fprintf(codegen_file, "if True == ");
            if (node->val.switch_stmt.caselist) {
                for (SWITCH_CASELIST *i = node->val.switch_stmt.caselist; i; i=i->next) {
                    if (i->default_case) {
                        if (j==0) {
                            fprintf(codegen_file, "True:\n");
                            codegenIndent(c_indent);
                        }
                        else {
                            codegenIndent(c_indent);
                            fprintf(codegen_file, "else:\n");
                        }
                    }
                    else {
                        if (j!=0) {
                            codegenIndent(c_indent);
                            fprintf(codegen_file, "elif ");
                            if (node->val.switch_stmt.condition->expr) {
                                if (node->val.switch_stmt.condition->expr->val.other_expr->kind == func_call_kind) {
                                    if (isFunction(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.id->data)) {
                                        fprintf(codegen_file, "_GOLITE__switchFuncCall");
                                    }
                                    else { // cast: simply remove the function call since we can only have one argument and Python is dynamically typed
                                        codegenEXPR(node->val.switch_stmt.condition->expr->val.other_expr->val.func_call.args->expr);
                                    }
                                }
                                else
                                    codegenEXPR(node->val.switch_stmt.condition->expr);
                            }
                            else
                                fprintf(codegen_file, "True");
                            fprintf(codegen_file, " == ");
                        }
                        //codegenEXPRLIST(i->exprlist);
                        if (i->exprlist) {
                            for (EXPRLIST *k = i->exprlist; k; k = k->next) {
                                if (k->expr) {
                                        if (k->expr->kind == other_expr_kind) {
                                            if (k->expr->val.other_expr->kind == func_call_kind) {
                                                if (isFunction(k->expr->val.other_expr->val.func_call.id->data)) {
                                                    //codegenIndent(c_indent);
                                                    codegenOTHER_EXPR(k->expr->val.other_expr->val.func_call.id);
                                                    fprintf(codegen_file, "(");
                                                    codegenEXPRLIST(k->expr->val.other_expr->val.func_call.args);
                                                    fprintf(codegen_file, ")");
                                                }
                                                else { // cast: simply remove the function call since we can only have one argument and Python is dynamically typed
                                                    codegenEXPR(k->expr->val.other_expr->val.func_call.args->expr);
                                                }
                                            }
                                            else
                                                codegenEXPR(k->expr);
                                        }
                                        else
                                            codegenEXPR(k->expr);
                                }
                                if (k->next) {
                                    fprintf(codegen_file, " or ");
                                    if (node->val.switch_stmt.condition->expr)
                                        codegenEXPR(node->val.switch_stmt.condition->expr);
                                    else
                                        fprintf(codegen_file, "True");
                                    fprintf(codegen_file, " == ");
                                }
                            }
                        }
                        fprintf(codegen_file, ":\n");
                        j++;
                    }
                    if (i->statements) {
                        c_indent++;
                        // for (STATEMENTS *i = node->val.for_stmt.block->stmts; i; i = i->next) {
                        //     if (i->stmt->kind == continue_stmt_s) {
                        //         STATEMENTS *post_stmt = makeSTATEMENTS(makeSTATEMENT_simple(node->val.for_stmt.condition->val.threepart.post), i);
                        //         node->val.for_stmt.block->stmts = post_stmt;
                        //         break;
                        //     }
                        // }
                        for (STATEMENTS *l = i->statements; l; l = l->next) {
                            if (l->stmt->kind == break_stmt_s) {
                                l->stmt = NULL;
                                l->next = NULL;
                                break;
                            }
                            else if (l->next && l->next->stmt->kind == break_stmt_s) {
                                l->next = NULL;
                            }
                        }
                        codegenSTATEMENTS(i->statements);
                        c_indent--;
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
            //codegenEXPRLIST(node->val.print);

            for (EXPRLIST *i = node->val.print; i; i = i->next) {
                fprintf(codegen_file, "str(");
                codegenEXPR(i->expr);
                fprintf(codegen_file, ").lower() if type(");
                codegenEXPR(i->expr);
                fprintf(codegen_file, ") is bool else ");
                codegenEXPR(i->expr);
                if (i->next) fprintf(codegen_file, ", ");
            }

            if (node->val.print)
                fprintf(codegen_file, ", ");
            fprintf(codegen_file, " sep='', end='')\n");
            break;
        case println_stmt_s:
            codegenIndent(c_indent);
            fprintf(codegen_file, "print(");
            //codegenEXPRLIST(node->val.print);

            for (EXPRLIST *i = node->val.print; i; i = i->next) {
                fprintf(codegen_file, "str(");
                codegenEXPR(i->expr);
                fprintf(codegen_file, ").lower() if type(");
                codegenEXPR(i->expr);
                fprintf(codegen_file, ") is bool else ");
                codegenEXPR(i->expr);
                if (i->next) fprintf(codegen_file, ", ");
            }

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
            /*
            if ((node->val.expr->kind == other_expr_kind) && (node->val.expr->val.other_expr->kind == identifier_kind)) {
                codegenIndent(c_indent);
                fprintf(codegen_file, "if '_GOLITE__%s' not in locals() and '_GOLITE__%s' in globals() and '_GOLITE__%s' not in func_globals:\n", node->val.expr->val.other_expr->val.identifier, node->val.expr->val.other_expr->val.identifier, node->val.expr->val.other_expr->val.identifier);
                c_indent++;
                codegenIndent(c_indent);
                fprintf(codegen_file, "global _GOLITE__%s\n", node->val.expr->val.other_expr->val.identifier);
                codegenIndent(c_indent);
                fprintf(codegen_file, "func_globals.append('_GOLITE__%s')\n", node->val.expr->val.other_expr->val.identifier);
                c_indent--;
            }
            */
            codegenIndent(c_indent);
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "+= 1\n");
            break;
        case decrement_kind:
            /*
            if ((node->val.expr->kind == other_expr_kind) && (node->val.expr->val.other_expr->kind == identifier_kind)) {
                codegenIndent(c_indent);
                fprintf(codegen_file, "if '_GOLITE__%s' not in locals() and '_GOLITE__%s' in globals() and '_GOLITE__%s' not in func_globals:\n", node->val.expr->val.other_expr->val.identifier, node->val.expr->val.other_expr->val.identifier, node->val.expr->val.other_expr->val.identifier);
                c_indent++;
                codegenIndent(c_indent);
                fprintf(codegen_file, "global _GOLITE__%s\n", node->val.expr->val.other_expr->val.identifier);
                codegenIndent(c_indent);
                fprintf(codegen_file, "func_globals.append('_GOLITE__%s')\n", node->val.expr->val.other_expr->val.identifier);
                c_indent--;
            }
            */
            codegenIndent(c_indent);
            codegenEXPR(node->val.expr);
            fprintf(codegen_file, "-= 1\n");
            break;
        case assignment_kind:
            /*
            for (EXPRLIST *i = node->val.assignment.LHS_expr_list; i; i = i->next) {
                if ((i->expr->kind == other_expr_kind) && (i->expr->val.other_expr->kind == identifier_kind) && (i->expr->kind != append_expr)) {
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "if '_GOLITE__%s' not in locals() and '_GOLITE__%s' in globals() and '_GOLITE__%s' not in func_globals:\n", i->expr->val.other_expr->val.identifier, i->expr->val.other_expr->val.identifier, i->expr->val.other_expr->val.identifier);
                    c_indent++;
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "global _GOLITE__%s\n", i->expr->val.other_expr->val.identifier);
                    codegenIndent(c_indent);
                    fprintf(codegen_file, "func_globals.append('_GOLITE__%s')\n", i->expr->val.other_expr->val.identifier);
                    c_indent--;
                }
            }
            */
            codegenIndent(c_indent);
            codegenEXPRLIST(node->val.assignment.LHS_expr_list);
            if (strcmp(node->val.assignment.assign_op, "&^=")==0)
                fprintf(codegen_file, " &= ~");
            if (node->val.assignment.RHS_expr_list->expr->kind != append_expr) {
                fprintf(codegen_file, " %s ", node->val.assignment.assign_op);
                //codegenEXPRLIST(node->val.assignment.RHS_expr_list);
                for (EXPRLIST *i = node->val.assignment.RHS_expr_list; i; i = i->next) {
                    DataType *res = resolveType(i->expr->data, node->symboltable, 1);
                    //if (i->expr->data->val.type->kind == slice_type_kind || i->expr->data->val.type->kind == array_type_kind || i->expr->data->val.type->kind == struct_type_kind) {
                    //if (res->val.type->kind == slice_type_kind || res->val.type->kind == array_type_kind || res->val.type->kind == struct_type_kind) {
                    if (res->val.type->kind == array_type_kind || res->val.type->kind == struct_type_kind) {
                    //if (res->val.type->kind == array_type_kind || res->val.type->kind == struct_type_kind) {
                        fprintf(codegen_file, "copy.deepcopy(");
                        codegenEXPR(i->expr);
                        fprintf(codegen_file, ")");
                    }
                    //fprintf(codegen_file, ") if type(");
                        else {
                            codegenEXPR(i->expr);
                        }
                    //fprintf(codegen_file, ") is list else ");
                    //codegenEXPR(i->expr);
                    if (i->next) fprintf(codegen_file, ", ");
                }
            }
            else { //append
                for (EXPRLIST *i = node->val.assignment.RHS_expr_list; i; i = i->next)
                    codegenEXPR(i->expr);
            }
            fprintf(codegen_file, "\n");
            break;
        case shortDcl_kind:
            codegenIndent(c_indent);
            codegenEXPRLIST(node->val.shortDcl.LHS_idlist);
            fprintf(codegen_file, " = ");
            //codegenEXPRLIST(node->val.shortDcl.RHS_expr_list);
            for (EXPRLIST *i = node->val.shortDcl.RHS_expr_list; i; i = i->next) {
                //fprintf(codegen_file, "copy.deepcopy(");
                codegenEXPR(i->expr);
                //fprintf(codegen_file, ")");
                if (i->next) fprintf(codegen_file, ", ");
            }
            fprintf(codegen_file, "\n");
            break;
    }
}

void codegenIDLIST(IDLIST *node) {
    for (IDLIST *i = node; i; i = i->next) {
        fprintf(codegen_file, "_GOLITE__%s", i->id);
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
            fprintf(codegen_file, ".append(");
            codegenEXPR(node->val.append_expr.expr);
            fprintf(codegen_file, ")");
            break;
        case intval:
        {
            //char *str = malloc(sizeof(char)*(int)log10(node->val.intLiteral));
            char *str = malloc(((sizeof(char) * sizeof(node->val.intLiteral) - 1) / 3 + 2));
            sprintf(str, "%d", node->val.intLiteral);
            // if (str[strspn(str, "0123456789abcdefABCDEF")] == 0) {
            //     //hex digit
            //     int num = (int)strtol(str, NULL, 16);
            //     fprintf(codegen_file, "%d", num);
            // }
            // else
            fprintf(codegen_file, "%d", node->val.intLiteral);
        }
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
            if (strlen(node->val.runeLiteral) == 3)
                fprintf(codegen_file, "%d", node->val.runeLiteral[1]);
            // convert escape character sequences to characters
            else if (node->val.runeLiteral[1] == '\\') {
                switch (node->val.runeLiteral[2]) {
                    case 'a':
                        fprintf(codegen_file, "%d", 7);
                        break;
                    case 'b':
                        fprintf(codegen_file, "%d", 8);
                        break;
                    case 'f':
                        fprintf(codegen_file, "%d", 12);
                        break;
                    case 'n':
                        fprintf(codegen_file, "%d", 10);
                        break;
                    case 'r':
                        fprintf(codegen_file, "%d", 13);
                        break;
                    case 't':
                        fprintf(codegen_file, "%d", 9);
                        break;
                    case 'v':
                        fprintf(codegen_file, "%d", 11);
                        break;
                    case '\\':
                        fprintf(codegen_file, "%d", 92);
                        break;
                    case '\'':
                        fprintf(codegen_file, "%d", 39);
                        break;
                }
            }
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
                fprintf(codegen_file, "_GOLITE__%s", node->val.identifier);
            break;
        case paren_kind:
            codegenEXPR(node->val.expr);
            break;
        case func_call_kind:
            if (isFunction(node->val.func_call.id->data)) {
                codegenIndent(c_indent);
                codegenOTHER_EXPR(node->val.func_call.id);
                fprintf(codegen_file, "(");

                for (EXPRLIST *i = node->val.func_call.args; i; i = i->next) {
                    DataType *res = resolveType(i->expr->data, node->symboltable, 1);
                    if (res->val.type->kind == array_type_kind || res->val.type->kind == struct_type_kind) {
                    //if (i->expr->data->val.type->kind == slice_type_kind || i->expr->data->val.type->kind == array_type_kind || i->expr->data->val.type->kind == struct_type_kind) {
                        fprintf(codegen_file, "copy.deepcopy(");
                        codegenEXPR(i->expr);
                        fprintf(codegen_file, ")");
                    }
                    else
                        codegenEXPR(i->expr);
                    if (i->next) fprintf(codegen_file, ", ");
                }

                //codegenEXPRLIST(node->val.func_call.args);
                fprintf(codegen_file, ")\n");
            }
            else { // cast: simply remove the function call since we can only have one argument and Python is dynamically typed
                if ((strcmp(node->val.func_call.id->val.identifier,"string") == 0)) {
                    if ((node->val.func_call.args->expr->val.other_expr->kind == identifier_kind) || (node->val.func_call.args->expr->kind == runeval)) {
                        fprintf(codegen_file, "chr(");
                        codegenEXPRLIST(node->val.func_call.args);
                        fprintf(codegen_file, ")");
                    }
                    else
                        codegenEXPR(node->val.func_call.args->expr);
                }
                else
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
            fprintf(codegen_file, "._GOLITE__%s", node->val.struct_access.identifier);
            break;
    }
}
