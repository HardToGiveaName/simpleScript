#ifndef __AST_H
#define __AST_H

#include <stdint.h>


typedef enum ast_node_type {
	Program,            //程序入口，根节点

	IntDeclaration,     //整型变量声明
	ExpressionStmt,     //表达式语句，即表达式后面跟个分号
	AssignmentStmt,     //赋值语句

	Primary,            //基础表达式
	Multiplicative,     //乘法表达式
	Additive,           //加法表达式

	tIdentifier,         //标识符
	tIntLiteral,         //整型字面量
} ASTNodeType;

typedef struct ast_node {
	struct ast_node *firstChild;
	struct ast_node *sibling;
	struct ast_node *parent;

	ASTNodeType type;
	char text[64]; //text的长度不能超过63
	uint8_t len;
} ASTNode;

typedef struct ast_node * AST;


AST ASTCreate(void);
ASTNode *ASTNodeCreate(ASTNodeType type, char *str);
int ASTAddChild(AST ast, AST ast1);
int ASTAddChild1(AST ast, ASTNodeType type, char *str);
void ASTDelete(AST ast);
void ASTPrint(AST ast, int n);  //n表示缩进的空格数

#endif
