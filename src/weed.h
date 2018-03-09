/* weeding makes a traversal of the AST and checks the following items:
 * 1. correct use of a blank identifier: The blank identifier may appear as an operand only on the left-hand side of an assignment. 
 */
    
#ifndef weed_H
#define weed_H

#include "tree.h"

void weedPROGRAM(PROGRAM *node);
void weedPACKAGE(PACKAGE *node);
void weedTOPLEVELDECL(TOPLEVELDECL *node);
void weedDCL(DCL *node);
void weedVARDCL(VARDCL *node);
void weedTYPEDCL(TYPEDCL *node);
void weedFUNCDCL(FUNCDCL *node);
int weedIDLIST(IDLIST *node);
void weedTYPE(TYPE *node);
int weedEXPRLIST(EXPRLIST *node);
void weedEXPR(EXPR *node);
void weedOTHER_EXPR(OTHER_EXPR *node);
void weedSWITCH_CASELIST(SWITCH_CASELIST *node);
void weedBLOCK(BLOCK *node);
void weedSTATEMENTS(STATEMENTS *node);
void weedSTATEMENT(STATEMENT *node);
void weedFUNC_SIGNATURE(FUNC_SIGNATURE *node);
void weedELSE_BLOCK(ELSE_BLOCK *node);
void weedSIMPLE(SIMPLE *node);

#endif /* !weed_H */

