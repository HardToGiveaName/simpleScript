#ifndef __AST_H
#define __AST_H

#include <stdint.h>


typedef enum ast_node_type {
	Program,            //������ڣ����ڵ�

	IntDeclaration,     //���ͱ�������
	ExpressionStmt,     //���ʽ��䣬�����ʽ��������ֺ�
	AssignmentStmt,     //��ֵ���

	Primary,            //�������ʽ
	Multiplicative,     //�˷����ʽ
	Additive,           //�ӷ����ʽ

	tIdentifier,         //��ʶ��
	tIntLiteral,         //����������
} ASTNodeType;

typedef struct ast_node {
	struct ast_node *firstChild;
	struct ast_node *sibling;
	struct ast_node *parent;

	ASTNodeType type;
	char text[64]; //text�ĳ��Ȳ��ܳ���63
	uint8_t len;
} ASTNode;

typedef struct ast_node * AST;


AST ASTCreate(void);
ASTNode *ASTNodeCreate(ASTNodeType type, char *str);
int ASTAddChild(AST ast, AST ast1);
int ASTAddChild1(AST ast, ASTNodeType type, char *str);
void ASTDelete(AST ast);
void ASTPrint(AST ast, int n);  //n��ʾ�����Ŀո���

#endif
