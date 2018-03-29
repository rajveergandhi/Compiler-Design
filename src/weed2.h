#ifndef weed2_H
#define weed2_H

#include "tree.h"

void weed2PROGRAM(PROGRAM *node);                        
void weed2TOPLEVELDECL(TOPLEVELDECL *node);              
void weed2FUNCDCL(FUNCDCL *node);
void weed2FUNC_SIGNATURE(FUNC_SIGNATURE *node);
bool isTerminating(STATEMENT *node);
bool hasBreak(STATEMENT *node);

#endif /* !weed2_H */