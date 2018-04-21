#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "weed2.h"

static bool hasReturn = false;

void weed2PROGRAM(PROGRAM *node) {
    weed2TOPLEVELDECL(node->topleveldecls);
}

void weed2TOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case func_dcl_toplevel:
                weed2FUNCDCL(i->val.funcdcl);
                break;
            case dcl_toplevel:
                break;
        }
    }
}

void weed2FUNCDCL(FUNCDCL *node) {
    if(node->signature)
        weed2FUNC_SIGNATURE(node->signature);
    STATEMENT *lastStatement = NULL;
    int ignoreSwitchInit = 0;
    if(node->block->stmts){
        for(STATEMENTS *i = node->block->stmts; i; i = i->next){
            validReturn(i->stmt);
        }
    }
    if(node->block->stmts && hasReturn){
        for(STATEMENTS *i = node->block->stmts; i; i = i->next){
            if(lastStatement == NULL)
                lastStatement = i->stmt;
            else if(lastStatement->kind == switch_stmt_s){
                if(ignoreSwitchInit == 0){
                    ignoreSwitchInit = 1;
                } else if(ignoreSwitchInit == 1){
                    ignoreSwitchInit = 0;
                    lastStatement = i->stmt;
                }
            }else{
                lastStatement = i->stmt;
            }
            if(!i->next){
                bool terminate = isTerminating(lastStatement);
                if(!terminate && hasReturn){
                    fprintf(stderr, "Error: function body must end in a terminating statement. (line %d)\n",lastStatement->lineno);
                    exit(1);
                }
            }
        }
    }else if(hasReturn){
        fprintf(stderr, "Error: function body must end in a terminating statement. (line %d)\n",node->lineno);
        exit(1);
    }
    hasReturn = false;
}

void validReturn(STATEMENT *node){
    if(node->kind == return_stmt_s){
        if(node->val.return_stmt && hasReturn == false){
                fprintf(stderr, "Error: returning value in a function with void return type. (line %d)\n",node->lineno);
                exit(1);
            }else if(!node->val.return_stmt && hasReturn == true){
                fprintf(stderr, "Error: not returning value in a function with non-void return type. (line %d)\n",node->lineno);
                exit(1);
            }

    }
}


void weed2FUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    if (node->type) {
        hasReturn = true;
    }
}



bool isTerminating(STATEMENT *node){
    switch(node->kind){
        case return_stmt_s:
            if(node->val.return_stmt && hasReturn == false){
                fprintf(stderr, "Error: returning value in a function with void return type. (line %d)\n",node->lineno);
                exit(1);
            }else if(!node->val.return_stmt && hasReturn == true){
                fprintf(stderr, "Error: not returning value in a function with non-void return type. (line %d)\n",node->lineno);
                exit(1);
            }
            return 1;
            break;
        case block_s:
        {
            STATEMENTS *i = NULL;
            if(node->val.block->stmts)
                i = node->val.block->stmts;
            else
                return false;
            while(i->next){
                i = i->next;
            }
            return isTerminating(i->stmt);
            break;
        }
        case if_stmt_s:
        {
            bool ifTerminating = false;
            bool elseTerminating = false;
            if(node->val.if_stmt.kind_else == no_else){
                return 0;
            }
            if(node->val.if_stmt.val.else_block.stmts){
                for(STATEMENTS *i = node->val.if_stmt.val.else_block.stmts; i; i = i->next){
                    if(!i->next)
                    ifTerminating = isTerminating(i->stmt);
                }
            }else{
                return 0;
            }
            if(node->val.if_stmt.kind_else == else_if){
                if(node->val.if_stmt.val.else_block.else_block->val.block->stmts && node->val.if_stmt.val.else_block.else_block->kind == block_else){
                    for(STATEMENTS *j = node->val.if_stmt.val.else_block.else_block->val.block->stmts; j; j = j->next){
                        if(!j->next){
                            elseTerminating = isTerminating(j->stmt);
                        }
                    }
                }else if(node->val.if_stmt.val.else_block.else_block->kind == if_stmt_else && node->val.if_stmt.val.else_block.else_block->val.if_stmt){
                    elseTerminating = isTerminating(node->val.if_stmt.val.else_block.else_block->val.if_stmt);
                }
                else{
                    return 0;
                }
            }
            return (ifTerminating && elseTerminating);
            break;
        }
        case for_stmt_s:
            if(node->val.for_stmt.condition->kind != threepart && node->val.for_stmt.condition->kind != infinite){
                return 0;
            }
            if(node->val.for_stmt.condition->val.threepart.condition && node->val.for_stmt.condition->kind == threepart){
                return 0;
            }
            for(STATEMENTS *i = node->val.for_stmt.block->stmts; i; i=i->next)
                if(hasBreak(i->stmt))
                   return 0;
            return 1;
            break;
        case switch_stmt_s:
        {
            bool isDefault = false;
            bool terminatingCases = true;
            if(node->val.switch_stmt.caselist){
                for(SWITCH_CASELIST *i = node->val.switch_stmt.caselist;i;i=i->next){
                    if(i->default_case)
                        isDefault = true;
                    if(i->statements){
                        for (STATEMENTS *j = i->statements; j; j=j->next){
                            if(hasBreak(j->stmt))
                                return 0;
                            if(!j->next)
                                if(!isTerminating(j->stmt))
                                    terminatingCases = false;
                        }
                    }else{
                        return 0;
                    }
                }
            }else{
                return 0;
            }
            if(isDefault == true && terminatingCases == true){
                return 1;
            }
            break;
        }
        case dcl_s:
        case simple_s:
        case break_stmt_s:
        case continue_stmt_s:
        case println_stmt_s:
        case print_stmt_s:
            return 0;
    }
    return 0;
}

bool hasBreak(STATEMENT *node){
    switch(node->kind){
        case dcl_s:
        case simple_s:
        case continue_stmt_s:
        case println_stmt_s:
        case print_stmt_s:
        case return_stmt_s:
            return false;
            break;
        case break_stmt_s:
            return true;
            break;
        case block_s:
            {
            STATEMENTS *i = NULL;
            if(node->val.block->stmts)
                i = node->val.block->stmts;
            else
                return false;
            while(i->next){
                if(hasBreak(i->stmt))
                    return true;
                i = i->next;
            }
            return false;
            break;
        }
        case if_stmt_s:
        {
            if(node->val.if_stmt.kind_else == no_else){
                if(node->val.if_stmt.val.if_block->stmts){
                    for(STATEMENTS *i = node->val.if_stmt.val.if_block->stmts; i; i = i->next){
                        if(hasBreak(i->stmt))
                            return true;
                    }
                }
            }            
            if(node->val.if_stmt.kind_else == else_if){
                if(node->val.if_stmt.val.else_block.stmts){
                    for(STATEMENTS *i = node->val.if_stmt.val.else_block.stmts; i; i = i->next){
                        if(hasBreak(i->stmt))
                            return true;
                    }
                }
                if(node->val.if_stmt.val.else_block.else_block->val.block->stmts && node->val.if_stmt.val.else_block.else_block->kind == block_else){
                    for(STATEMENTS *j = node->val.if_stmt.val.else_block.else_block->val.block->stmts; j; j = j->next){
                        if(hasBreak(j->stmt))
                            return true;
            
                    }
                }else if(node->val.if_stmt.val.else_block.else_block->kind == if_stmt_else && node->val.if_stmt.val.else_block.else_block->val.if_stmt){
                    return hasBreak(node->val.if_stmt.val.else_block.else_block->val.if_stmt);
                }
            }
            return false;
            break;
        }
        case for_stmt_s:
        {
            if(node->val.for_stmt.block->stmts){
                for(STATEMENTS *i = node->val.for_stmt.block->stmts; i; i=i->next)
                    if(hasBreak(i->stmt))
                        return true;
            }
            return false;
            break;
        }
        case switch_stmt_s:
        {
            if(node->val.switch_stmt.caselist){
                for(SWITCH_CASELIST *i = node->val.switch_stmt.caselist;i;i=i->next){
                    if(i->statements){
                        for (STATEMENTS *j = i->statements; j; j=j->next){
                            if(hasBreak(j->stmt))
                                return true;
                        }
                    }
                }
            }
            return false;
            break;
        }
    }
    return false;
}
