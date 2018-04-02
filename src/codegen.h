#ifndef CODEGEN_H
#define CODEGEN_H

#include "tree.h"

void codegenPROGRAM(PROGRAM *node);
void codegenTOPLEVELDECL(TOPLEVELDECL *node);
void codegenDCL(DCL *node);
void codegenVARDCL(VARDCL *node);
void codegenTYPEDCL(TYPEDCL *node);
void codegenFUNCDCL(FUNCDCL *node);
void codegenFUNC_SIGNATURE(FUNC_SIGNATURE *node);
void codegenBLOCK(BLOCK *node);
void codegenSTATEMENTS(STATEMENTS *node);
void codegenSTATEMENT(STATEMENT *node);
void codegenIDLIST(IDLIST *node);
void codegenEXPRLIST(EXPRLIST *node);
void codegenEXPR(EXPR *node);

#endif /* !CODEGEN_H */
