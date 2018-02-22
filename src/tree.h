#ifndef TREE_H
#define TREE_H

typedef enum {
	k_expressionKindProgram,
	k_expressionKindDeclaration,
	k_expressionKindRead,
	k_expressionKindPrint,
	k_expressionKindAssign,
	k_expressionKindIf,
	k_expressionKindIfElse,
	k_expressionKindWhile,
	k_expressionKindIdentifier,
	k_expressionKindIntLiteral,
	k_expressionKindFloatLiteral,
	k_expressionKindStringLiteral,
	k_expressionKindBoolLiteral,
	k_expressionKindAddition,
	k_expressionKindSubtraction,
	k_expressionKindMultiplication,
	k_expressionKindDivision,
	k_expressionKindEquals,
	k_expressionKindNotEquals,
	k_expressionKindAnd,
	k_expressionKindOr,
	k_expressionKindNot,
	k_expressionKindUnaryMinus
	
} ExpressionKind;

typedef struct SYMBOL{
	char *name;
	ExpressionKind kind;
	ExpressionKind kind_c;
	struct SYMBOL *next;
} SYMBOL;

typedef struct TYPE{
	int lineno;
	enum {
		tINTVAL,
		tBOOLVAL,
		tSTRINGVAL,
		tFLOATVAL,
	} kind;
} TYPE;

typedef struct AST AST;
struct AST {
	int lineno;
	ExpressionKind kind;
	ExpressionKind kind_c;
	union {
		char *identifier;
		int intLiteral;
		double floatLiteral;
		char *stringLiteral;
		int boolLiteral;
		struct { AST *rhs;  } notN;
		struct { AST *rhs; } unaryminusN;
		struct { char *id; ExpressionKind kind; char *type; AST *rhs; AST *next; } dclN;
		struct { AST *dcls; AST *stmts; } programN;
		struct { AST *lhs; AST *rhs; } binaryN;
		struct 
		{
			union{
				struct { char *lhs; AST *rhs; SYMBOL *leftsym;} assignN;
				struct { AST *rhs; } printN;
				struct { char *id; } readN;
				struct { AST *condition; AST *body; int stoplabel; } ifN;
		    	struct { AST *condition; AST *thenpart; AST *elsepart; int elselabel,stoplabel; } ifelseN;
				struct { AST *condition; AST *body; int startlabel,stoplabel; } whileN;
			} stmtval;
			struct AST *next;
		} stmt;
	} val;
};

AST *makeTREE_identifier(char *id);
AST *makeTREE_intLiteral(int intLiteral);
AST *makeTREE_floatLiteral(double floatLiteral);
AST *makeTREE_stringLiteral(char *stringLiteral);
AST *makeTREE_boolLiteral(int boolLiteral);

AST *makeTREE_binaryexpr(ExpressionKind op, AST *lhs, AST *rhs);
AST *makeTREE_notexpr(ExpressionKind op, AST *rhs);
AST *makeTREE_unaryminus(ExpressionKind op, AST *rhs);


AST *makeTREE_program(AST *dcls, AST *stmts);
AST *makeTREE_dcl(char *id, ExpressionKind kind, char *type, AST *rhs);
AST *next_dcl(AST *dcl, AST *dcls);
AST *next_stmt(AST *stmt, AST *stmts);

AST *makeTREE_print(AST *rhs);
AST *makeTREE_read(char *id);
AST *makeTREE_assign(char *lhs, AST *rhs);
AST *makeTREE_while(AST *condition, AST *body);
AST *makeTREE_if(AST *condition, AST *body);
AST *makeTREE_ifelse(AST *condition, AST *thenpart, AST *elsepart);



#endif /* !TREE_H */