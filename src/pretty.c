#include <stdio.h>
#include <stdlib.h>
#include "pretty.h"

// global indentation variable; it is incremented whenever necessary (if or while statement)
int g_indent = 0;

void prettyIndent(int indent_level) {
    int indent_val = 4; // one level of indentation is defined as 4 spaces
    for (int i = 0; i < indent_val * indent_level; ++i) {
        printf(" ");
    }
}
void prettyPROGRAM(PROGRAM *node) {
    prettyPACKAGE(node->package);
    prettyTOPLEVELDECL(node->topleveldecls);
}

void prettyPACKAGE(PACKAGE *node) {
    printf("package %s\n", node->package);
}

void prettyTOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case dcl_toplevel:
                prettyDCL(i->val.dcl);
                break;
            case func_dcl_toplevel:
                prettyFUNCDCL(i->val.funcdcl);
                break;
        }
    }
}

void prettyDCL(DCL *node) {
    switch (node->kind) {
        case var:
            prettyVARDCL(node->val.vardcl);
            break;
        case type:
            prettyTYPEDCL(node->val.typedcl);
            break;
    }
}

void prettyVARDCL(VARDCL *node) {
    for (VARDCL *i = node; i; i = i->next) {
        printf("var ");
        prettyIDLIST(i->idlist);
        if (i->type) {
            printf(" ");
            prettyTYPE(i->type);
        }
        if (i->exprlist) {
            printf(" = ");
            prettyEXPRLIST(i->exprlist);
        }
        printf("\n");
    }
}

void prettyTYPEDCL(TYPEDCL *node) {
    for (TYPEDCL *i = node; i; i = i->next) {
        printf("type ");
        printf("%s ", i->identifier);
        prettyTYPE(i->type);
        printf("\n");
    }
}

void prettyFUNCDCL(FUNCDCL *node) {
    printf("func %s", node->identifier);
    prettyFUNC_SIGNATURE(node->signature);
    printf(" ");
    prettyBLOCK(node->block);
}

void prettyFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    printf("(");
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        prettyIDLIST(i->idlist);
        printf(" ");
        prettyTYPE(i->type);
        if (i->next)
            printf(", ");
    }
    printf(")");
    if (node->type) {
        printf(" ");
        prettyTYPE(node->type);
    }
}

void symPrettyFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        prettyTYPE(i->type);
        if (i->next)
            printf(", ");
    }
    if (node->type) {
        printf(") -> ");
        prettyTYPE(node->type);
    }
    else
        printf(") -> void ");

    printf("\n");
}

void prettyIDLIST(IDLIST *node) {
    for (IDLIST *i = node; i; i = i->next) {
        printf("%s", i->id);
        if (i->next) printf(", ");
    }
}

void prettyBLOCK(BLOCK *node) {
    printf("{\n");
    prettySTATEMENTS(node->stmts);
    printf("}\n");
}

void prettySTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next) {
        prettySTATEMENT(i->stmt);
    }
}

void prettySTATEMENT(STATEMENT *node) {
    switch(node->kind) {
        case dcl_s:
            prettyDCL(node->val.dcl);
            break;
        case simple_s:
            prettySIMPLE(node->val.simple);
            break;
        case return_stmt_s:
            printf("return");
            if (node->val.return_stmt) {
                printf(" ");
                prettyEXPR(node->val.return_stmt);
            }
            printf("\n");
            break;
        case break_stmt_s:
            printf("break\n");
            break;
        case continue_stmt_s:
            printf("continue\n");
            break;
        case block_s:
            prettyBLOCK(node->val.block);
            break;
        case if_stmt_s:
            printf("if ");
            if (node->val.if_stmt.simple) {
                prettySIMPLE(node->val.if_stmt.simple);
                printf("; ");
            }
            prettyEXPR(node->val.if_stmt.expr);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    prettyBLOCK(node->val.if_stmt.val.if_block);
                    break;
                case else_if:
                    printf("{\n");
                    prettySTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    printf("}");
                    prettyELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    break;
            }
            break;
        case switch_stmt_s:
            printf("switch ");
            if (node->val.switch_stmt.condition->simple) {
                prettySIMPLE(node->val.switch_stmt.condition->simple);
                printf("; ");
            }
            if (node->val.switch_stmt.condition->expr) {
                prettyEXPR(node->val.switch_stmt.condition->expr);
                printf(" ");
            }
            if (node->val.switch_stmt.caselist)
                prettySWITCH_CASELIST(node->val.switch_stmt.caselist);
            break;
        case for_stmt_s:
            printf("for ");
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    break;
                case while_loop:
                    prettyEXPR(node->val.for_stmt.condition->val.while_expr);
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init) {
                        prettySIMPLE(node->val.for_stmt.condition->val.threepart.init);
                        printf(" ");
                    }
                    if (node->val.for_stmt.condition->val.threepart.condition) {
                        prettyEXPR(node->val.for_stmt.condition->val.threepart.condition);
                        printf(";");
                    }
                    if (node->val.for_stmt.condition->val.threepart.post)
                        prettySIMPLE(node->val.for_stmt.condition->val.threepart.post);
                    break;
            }
            prettyBLOCK(node->val.for_stmt.block);
            break;
        case print_stmt_s:
            printf("print (");
            prettyEXPRLIST(node->val.print);
            printf(")\n");
            break;
        case println_stmt_s:
            printf("println (");
            prettyEXPRLIST(node->val.print);
            printf(")\n");
            break;
    }
}

void prettySWITCH_CASELIST(SWITCH_CASELIST *node) {
    printf("{\n");
    for (SWITCH_CASELIST *i = node; i; i=i->next) {
        if (i->default_case) {
            printf("default:\n");
        }
        else {
            printf("case ");
            prettyEXPRLIST(i->exprlist);
            printf(":\n");
        }
        if (i->statements)
            prettySTATEMENTS(i->statements);
    }
    printf("}\n");
}

void prettyELSE_BLOCK(ELSE_BLOCK *node) {
    printf(" else ");
    switch (node->kind) {
        case if_stmt_else:
            prettySTATEMENT(node->val.if_stmt);
            break;
        case block_else:
            prettyBLOCK(node->val.block);
            break;
    }
}

void prettySIMPLE(SIMPLE *node) {
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            prettyEXPR(node->val.expr);
            break;
        case increment_kind:
            prettyEXPR(node->val.expr);
            printf("++");
            break;
        case decrement_kind:
            prettyEXPR(node->val.expr);
            printf("--");
            break;
        case assignment_kind:
            prettyEXPRLIST(node->val.assignment.LHS_expr_list);
            printf(" %s ", node->val.assignment.assign_op);
            prettyEXPRLIST(node->val.assignment.RHS_expr_list);
            printf("\n");
            break;
        case shortDcl_kind:
            prettyIDLIST(node->val.shortDcl.LHS_idlist);
            printf(" := ");
            prettyEXPRLIST(node->val.shortDcl.RHS_expr_list);
            printf(";");
            break;
    }
}

void prettyTYPE(TYPE *node) {
    switch (node->kind) {
        case basic_type_kind:
            printf("%s", node->val.basic_type);
            break;
        case slice_type_kind:
            printf("[");
            printf("]");
            prettyTYPE(node->val.slice_type);
            break;
        case array_type_kind:
            printf("[");
            printf("%d", node->val.array_type.size);
            printf("]");
            prettyTYPE(node->val.array_type.type);
            break;
        case struct_type_kind:
            printf("struct {");
            for (STRUCT_TYPE *i = node->val.struct_type; i; i = i->next) {
                prettyIDLIST(i->idlist);
                printf (" ");
                prettyTYPE(i->type);
                printf("; ");
            }
            printf("}");
            break;
    }
}

void prettyEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next) {
        prettyEXPR(i->expr);
        if (i->next) printf(", ");
    }
}

void prettyEXPR(EXPR *node) {
    switch (node->kind) {
        case expressionKindPlus:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" + ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindMinus:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" - ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindMult:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" * ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindDiv:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" / ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindMod:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" %% ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindLT:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" < ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindLT_EQ:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" <= ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindGT:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" > ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindGT_EQ:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" >= ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindEQ_EQ:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" == ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindNotEquals:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" != ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindShift_Right:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" >> ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindShift_Left:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" << ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindAnd:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" & ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindAMP_XOR:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" &^ ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindOr:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" | ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindXor:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" ^ ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindLogicalAnd:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" && ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindLogicalOr:
            printf("(");
            prettyEXPR(node->val.binary.lhs);
            printf(" || ");
            prettyEXPR(node->val.binary.rhs);
            printf(")");
            break;
        case expressionKindPlusUnary:
            printf("(+(");
            prettyEXPR(node->val.expr_unary);
            printf(")");
            break;
        case expressionKindMinusUnary:
            printf("(-(");
            prettyEXPR(node->val.expr_unary);
            printf(")");
            break;
        case expressionKindNotUnary:
            printf("(!(");
            prettyEXPR(node->val.expr_unary);
            printf(")");
            break;
        case expressionKindXorUnary:
            printf("(^(");
            prettyEXPR(node->val.expr_unary);
            printf(")");
            break;
        case append_expr:
            printf("append(%s, ", node->val.append_expr.identifier);
            prettyEXPR(node->val.append_expr.expr);
            printf(")\n");
            break;
        case intval:
            printf("%d", node->val.intLiteral);
            break;
        case floatval:
            printf("%f", node->val.floatLiteral);
            break;
        case stringval:
            printf("%s", node->val.stringLiteral);
            break;
        case rawstringval:
            printf("%s", node->val.stringLiteral);
            break;
        case runeval:
            printf("%s", node->val.runeLiteral);
            break;
        case other_expr_kind:
            prettyOTHER_EXPR(node->val.other_expr);
            break;
    }
}

void prettyOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            printf("%s", node->val.identifier);
            break;
        case paren_kind:
            prettyEXPR(node->val.expr);
            break;
        case func_call_kind:
            prettyOTHER_EXPR(node->val.func_call.id);
            printf("(");
            prettyEXPRLIST(node->val.func_call.args);
            printf(")");
            break;
        case index_kind:
            prettyOTHER_EXPR(node->val.index.expr);
            printf("[");
            prettyEXPR(node->val.index.index);
            printf("]");
            break;
        case struct_access_kind:
            prettyOTHER_EXPR(node->val.struct_access.expr);
            printf(".%s", node->val.struct_access.identifier);
            break;
    }
}
