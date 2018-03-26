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
void typeSIMPLE(SIMPLE *node);

// helper functions
void isBool(DataType *base, int lineno);
void isInteger(DataType *base, int lineno);
void isNumeric(DataType *base, int lineno);
void isNumericOrString(DataType *base, int lineno);
void isBaseType(DataType *data, int lineno);
void mustHaveSameType(DataType *data1, DataType *data2, int lineno);
bool isFunction(DataType *data);
void validCast(DataType *typedata, DataType *exprdata, int lineno);
DataType *isSlice(DataType *data, int lineno);
DataType *isSliceOrArray(DataType *data, int lineno);
void isStruct(DataType *data, int lineno);
DataType *resolveType(DataType *data, SymbolTable *sym, int lineno);
