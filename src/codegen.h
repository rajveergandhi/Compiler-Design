#ifndef CODEGEN_H
#define CODEGEN_H

#include "tree.h"

void codegenPROGRAM(PROGRAM *node);
void codegenTOPLEVELDECL(TOPLEVELDECL *node);
void codegenDCL(DCL *node);
void codegenVARDCL(VARDCL *node);
void codegenTYPE(TYPE *node);
void codegenTYPEDCL(TYPEDCL *node);
void codegenFUNCDCL(FUNCDCL *node);
void codegenFUNC_SIGNATURE(FUNC_SIGNATURE *node);
void codegenBLOCK(BLOCK *node);
void codegenSTATEMENTS(STATEMENTS *node);
void codegenSTATEMENT(STATEMENT *node);
void codegenSWITCH_CASELIST(SWITCH_CASELIST *node);
void codegenELSE_BLOCK(ELSE_BLOCK *node);
void codegenSIMPLE(SIMPLE *node);
void codegenIDLIST(IDLIST *node);
void codegenEXPRLIST(EXPRLIST *node);
void codegenEXPR(EXPR *node);
void codegenOTHER_EXPR(OTHER_EXPR *node);

#endif /* !CODEGEN_H */
