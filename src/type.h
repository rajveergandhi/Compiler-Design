#include "tree.h"

void typePROGRAM(PROGRAM *node);
void typeTOPLEVELDECL(TOPLEVELDECL *node);
void typeDCL(DCL *node);
void typeVARDCL(VARDCL *node);
void typeTYPEDCL(TYPEDCL *node);
void typeFUNCDCL(FUNCDCL *node);
void typeEXPR(EXPR *node);
void typeOTHER_EXPR(OTHER_EXPR *node);
void typeEXPRLIST(EXPRLIST *node);
void typeBLOCK(BLOCK *node);
void typeSTATEMENTS(STATEMENTS *node);
void typeSTATEMENT(STATEMENT *node);
void typeSWITCH_CASELIST(SWITCH_CASELIST *node, symTYPE *symtype);

// helper functions
bool isBool(symTYPE *base, int lineno);
bool isInteger(symTYPE *base, int lineno);
bool isNumeric(symTYPE *base, int lineno);
bool isNumericOrString(symTYPE *base, int lineno);
bool hasSameType(symTYPE *base1, symTYPE *base2, int lineno);
