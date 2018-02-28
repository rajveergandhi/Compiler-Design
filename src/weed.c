#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "weed.h"
static bool hasDefault = false;
static bool insideFor = false;
static bool insideSwitch = false;
static bool isBlankIdValid = false;

void weedPROGRAM(NODE *p){
	if(p!=NULL){
		for(NODE *i = p; i->val.program.topLevelDecls != NULL; i = i->val.program.topLevelDecls->val.next){
			weedTOPLEVELDECLS(i->val.program.topLevelDecls);
		}
	}
}
void weedTOPLEVELDECLS(NODE *d){
	for (NODE *TOPLEVEL = d; TOPLEVEL; ) {
		if(TOPLEVEL->kind == k_function){
			weedBLOCK(TOPLEVEL->val.toplevel.type.funcDcl.block);
			TOPLEVEL = TOPLEVEL->val.toplevel.next;
		} else if(TOPLEVEL->kind == k_dcl_var){
			for(NODE *i = TOPLEVEL; i != NULL; i = i->val.toplevel.type.varDcl.next){
				isBlankIdValid = true;
			}
			isBlankIdValid = false;
			TOPLEVEL = TOPLEVEL->val.toplevel.next;
		} else {
			if (TOPLEVEL != NULL)
				TOPLEVEL = TOPLEVEL->val.toplevel.next;
		}
	}
}
void weedBLOCK(NODE *b){
	if(b->val.stmt.type.block.stmts){
		weedSTATEMENT(b->val.stmt.type.block.stmts);
	}
}

void weedSTATEMENT(NODE *stmt){
	switch(stmt->kind){
		case k_statementKindSwitch:
			insideSwitch = true;
			weedSTATEMENT(stmt->val.stmt.type.stmtSwitch.caselist);
			insideSwitch = false;
			break;
		case k_statementKindSwitchCase:
			insideSwitch = true;
			if(!stmt->val.stmtSwitchCase.expr_list && !hasDefault){
				hasDefault = true;
			}
			else if(!stmt->val.stmtSwitchCase.expr_list && hasDefault){
				fprintf(stderr, "Error: (line %d) a switch-case block can only have one default block\n", stmt->lineno);
				exit(1);
			}
			if (stmt->val.stmtSwitchCase.next){
                weedSTATEMENT(stmt->val.stmtSwitchCase.next);
            }
            else
            	hasDefault = false;
			break;
		case k_statementKindFor:
			insideFor = true;
			weedSTATEMENT(stmt->val.stmt.type.stmtFor.block);
			insideFor = false;
			break;
		case k_statementKindIf:
			weedBLOCK(stmt->val.stmt.type.stmtIf.stmts);
			if (stmt->val.stmt.type.stmtIf.elseBlock) {
                weedBLOCK(stmt->val.stmt.type.stmtIf.elseBlock);
            }
            break;
		case k_statementKindBreak:
			if(!insideFor && !insideSwitch){
				fprintf(stderr, "Error: (line %d) break statements can only be inside a for loop or switch block\n", stmt->lineno);
				exit(1);
			}
			break;
		case k_statementKindContinue:
			if(!insideFor){
				fprintf(stderr, "Error: (line %d) continue statements can only be inside a for loop\n", stmt->lineno);
				exit(1);
			}
			break;
		case k_statementKindAssign:
			isBlankIdValid = true;
			weedEXPRESSION(stmt->val.stmt.type.stmtShortDcl.LHS_expr_list);
			isBlankIdValid = false;
			break;

	}
	if(stmt->val.stmt.next)
		weedSTATEMENT(stmt->val.stmt.next);
}

void weedEXPRESSION(NODE *node){
	switch(node->kind){
	 	case k_expressionKindIdentifier:
	 		if(!isBlankIdValid){
            	fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
            	exit(1);
            }
            break;
        case k_expressionKindPlus:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMinus:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMult:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindDiv:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMod:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLT:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLT_EQ:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindGT:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindGT_EQ:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindEQ_EQ:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindNotEquals:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindShift_Right:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindShift_Left:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindAnd:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindAMP_XOR:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindOr:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindXor:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLogicalAnd:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLogicalOr:
            weedEXPRESSION(node->val.expr.type.exp_binary.lhs);
            weedEXPRESSION(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindNotUnary:
            weedEXPRESSION(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindPlusUnary:
            weedEXPRESSION(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindMinusUnary:
            weedEXPRESSION(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindXorUnary:
            weedEXPRESSION(node->val.expr.type.exp_unary);
            break;
    }
    if(node->val.stmt.next)
		weedSTATEMENT(node->val.stmt.next);
}
