/* weeding makes a traversal of the AST and checks the following items:
 * 1. correct use of a blank identifier: The blank identifier may appear as an operand only on the left-hand side of an assignment or as identifier in a top-level declaration. 
 * 2. return statements : return statements can only be inside a function body
 * 3. break statements : break statements can only be inside a for loop, switch block or if block
 * 4. continue statements : continue statements can only be inside a for loop
 * 5. assignment and short declarations : The operands on L.H.S. of a short declaration or assignment must be equal to the number of expressions in the R.H.S.
 * 6. default statement : every switch block should have at most one default case.
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

