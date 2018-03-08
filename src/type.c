#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "type.h"

TYPE *type_true, *type_false, *type_int, *type_float64, *type_rune, *type_bool, *type_string;

void initTypes() {
    SYMBOL *s;
    *type_true = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    *type_false = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    *type_int = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "int";
    *type_float64 = malloc(sizeof(TYPE)); type_float64->kind = basic_type_kind; type_float64->val.basic_type = "float64";
    *type_rune = malloc(sizeof(TYPE)); type_rune->kind = basic_type_kind; type_rune->val.basic_type = "rune";
    *type_bool = malloc(sizeof(TYPE)); type_bool->kind = basic_type_kind; type_bool->val.basic_type = "bool";
    *type_string = malloc(sizeof(TYPE)); type_string->kind = basic_type_kind; type_string->val.basic_type = "string";
    // s = getSymbol(classlib,"String");
    // if (s==NULL) {
    //     reportGlobalError("class String not found");
    //     noErrors();
    // }
}
int equalTYPE(TYPE *s, TYPE *t) {
    if (s->val.basic_type!=t->val.basic_type) return 0;
    // if (s->kind==refK) {
    //     return strcmp(s->name,t->name)==0;
    // }
    return 1;
}
int integerTYPE(TYPE *t) {
    return t->val.basic_type=="int";
}
int assignTYPE(TYPE *s, TYPE *t) {
    if (s->val.basic_type!=t->val.basic_type) return 0;
    return 1;
}

int checkBOOL(TYPE *t, int lineno) {
    if (t->val.basic_type!="bool") {
        reportError("boolean type expected",lineno);
        return 0;
    }
    return 1;
}
int checkRUNE(TYPE *t, int lineno) {
    if (t->val.basic_type!="rune") {
        reportError("rune type expected",lineno);
        return 0;
    }
    return 1;
}
int checkSTRING(TYPE *t, int lineno) {
    if (t->val.basic_type!="string") {
        reportError("string type expected",lineno);
        return 0;
    }
    return 1;
}
int checkINT(TYPE *t, int lineno) {
    if (t->val.basic_type!="int") {
        reportError("int type expected",lineno);
        return 0;
    }
    return 1;
}
// int equalFORMAL(FORMAL *f, FORMAL *g) {
//     if (f==NULL || g==NULL) return f==NULL && g==NULL;
//     return equalTYPE(f->type,g->type) && equalFORMAL(f->next,g->next);
// }


void typePROGRAM(PROGRAM *node) {
    initTypes();
    typePROGRAM(node);
}

void typePROGRAM(PROGRAM *node) {
    if (node!=NULL) {
        typeTOPLEVELDECL(node->topleveldecls);
    }
}
void typeTOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        if (i->kind == func_dcl_toplevel) {
            typeFUNCDCL(i->val.funcdcl);
        }
    }
}
void typeFUNCDCL(FUNCDCL *node) {
    switch(node->identifier) {
        case "init":
            typeIntMainFUNC_SIGNATURE(node->signature);
            typeIntMainBLOCK(node->block);
            break;
        case "main":
            typeIntMainFUNC_SIGNATURE(node->signature);
            typeIntMainBLOCK(node->block);
            break;
        default:
            typeFUNC_SIGNATURE(node->signature);
            typeBLOCK(node->block);
            break;
    }

}
void typeIntMainFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    if(node->params!=NULL) {
        //error
    }
}
void typeIntMainBLOCK(BLOCK *node) {
    typeIntMainSTATEMENTS(node->stmts);
}
void typeIntMainSTATEMENTS(STATEMENTS *node) {
    int checkRETURN = 0;
    for (STATEMENTS *i = node; i; i = i->next) {
        if (i->stmt->kind == return_stmt_s)
            checkRETURN = 1;
    }
    if (!checkRETURN) {
        // error
    }
}





void typeFUNC_SIGNATURE(FUNC_SIGNATURE *node) {

}
void typeBLOCK(BLOCK *node) {
    typeSTATEMENTS(node->stmts);
}
void typeSTATEMENTS(STATEMENTS *node) {
    int checkRETURN = 0;
    for (STATEMENTS *i = node; i; i = i->next) {
        if (i->stmt->kind == return_stmt_s)
            checkRETURN = 1;
    }
}
