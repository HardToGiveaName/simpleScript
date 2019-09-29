#include "ast.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>


AST ASTCreate(void)
{
	ASTNode *pn;

	pn = (ASTNode *)malloc(sizeof(ASTNode));
	if (pn != NULL)
	{
		pn->parent = NULL;
		pn->firstChild = NULL;
		pn->sibling = NULL;
		pn->type = Program;
		strcpy(pn->text, "");
		pn->len = (uint8_t)strlen("");
	}

	return pn;
}

ASTNode *ASTNodeCreate(ASTNodeType type, char *str)
{
	ASTNode *pn;

	pn = (ASTNode *)malloc(sizeof(ASTNode));
	if (pn != NULL)
	{
		pn->parent = NULL;
		pn->firstChild = NULL;
		pn->sibling = NULL;
		pn->type = type;
		strcpy(pn->text, str);
		pn->len = (uint8_t)strlen(str);
	}

	return pn;
}

int ASTAddChild(AST ast, AST ast1)
{
	ASTNode *pn;

	if (ast == NULL)
		return -1;

	if (ast->firstChild == NULL)
	{
		ast->firstChild = ast1;
	}
	else
	{
		pn = ast->firstChild;
		while (pn->sibling != NULL)
			pn = pn->sibling;
		pn->sibling = ast1;
	}
	ast1->parent = ast;

	return 1;
}

int ASTAddChild1(AST ast, ASTNodeType type, char *str)
{
	ASTNode *pn;
	ASTNode *p;

	if (ast == NULL)
		return -1;

	pn = (ASTNode *)malloc(sizeof(ASTNode));
	if (pn == NULL)
		return 0;

	pn->parent = NULL;
	pn->firstChild = NULL;
	pn->sibling = NULL;
	pn->type = type;
	strcpy(pn->text, str);
	pn->len = (uint8_t)strlen(str);

	if (ast->firstChild == NULL)
	{
		ast->firstChild = pn;
	}
	else
	{
		p = pn->firstChild;
		while (p->sibling != NULL)
			p = p->sibling;
		p->sibling = pn;
	}
	pn->parent = ast;

	return 1;
}

void ASTDelete(AST ast)
{
	if (ast == NULL)
		return;
	else
	{
		ASTDelete(ast->firstChild);
		ASTDelete(ast->sibling);
		free(ast);
	}
}

void ASTPrint(AST ast, int n)
{
	ASTNode *pn;

	if (ast == NULL)
		return;

	for (int i = 0; i < n; i++)
		printf("  ");
	printf("%s\r\n", ast->text);

	pn = ast->firstChild;
	while (pn != NULL)
	{
		ASTPrint(pn, n + 1);
		pn = pn->sibling;
	}
}
