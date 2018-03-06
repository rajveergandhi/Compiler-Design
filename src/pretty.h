#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyPROGRAM(PROGRAM *node);
void prettyPACKAGE(PACKAGE *node);
void prettyTOPLEVELDECL(TOPLEVELDECL *node);
void prettyDCL(DCL *node);
void prettyVARDCL(VARDCL *node);
void prettyTYPEDCL(TYPEDCL *node);
void prettyFUNCDCL(FUNCDCL *node);
void prettyIDLIST(IDLIST *node);
void prettyTYPE(TYPE *node);
void prettyEXPRLIST(EXPRLIST *node);
void prettyEXPR(EXPR *node);
void prettyOTHER_EXPR(OTHER_EXPR *node);
void prettySWITCH_CASELIST(SWITCH_CASELIST *node);
void prettyBLOCK(BLOCK *node);
void prettySTATEMENTS(STATEMENTS *node);
void prettySTATEMENT(STATEMENT *node);
void prettyFUNC_SIGNATURE(FUNC_SIGNATURE *node);
void prettyELSE_BLOCK(ELSE_BLOCK *node);
void prettySIMPLE(SIMPLE *node);

#endif /* !PRETTY_H */

