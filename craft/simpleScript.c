#include "simpleScript.h"
#include "variable.h"
#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static Variables vars;
static int err;

static int evaluate(ASTNode *pn, int n)
{
	ASTNode *pn1, *child1, *child2;
	int res, res1, res2;
	Variable *pVar;

	switch (pn->type)
	{
	case Program:
		pn1 = pn->firstChild;
		while (pn1 != NULL)
		{
			err = 0;
			res = evaluate(pn1, n + 1);
			pn1 = pn1->sibling;
		}
		break;
	case Additive:
		child1 = pn->firstChild;
		child2 = pn->firstChild->sibling;
		res1 = evaluate(child1, n + 1);
		res2 = evaluate(child2, n + 1);
		if (strcmp(pn->text, "+")==0)
			res = res1 + res2;
		else
			res = res1 - res2;
		break;
	case Multiplicative:
		child1 = pn->firstChild;
		child2 = pn->firstChild->sibling;
		res1 = evaluate(child1, n + 1);
		res2 = evaluate(child2, n + 1);
		if (strcmp(pn->text, "*") == 0)
			res = res1 * res2;
		else
			res = res1 / res2;
		break;
	case tIntLiteral:
		res = atoi(pn->text);
		break;
	case tIdentifier:
		pVar = VariablesFind(vars, pn->text);
		if (pVar != NULL)
		{
			if (pVar->valid == 0)
			{
				printf("variable %s has not been set any value\n", pn->text);
				err = 1;
				res = 0;
			}
			else
				res = pVar->value;
		}
		else
		{
			printf("unknown variable: %s\n", pn->text);
			err = 1;
			res = 0;
		}
		break;
	case AssignmentStmt:
		pVar = VariablesFind(vars, pn->text);
		if (pVar != NULL)
		{
			child1 = pn->firstChild;
			res = evaluate(child1, n + 1);
			if (err == 0)
			{
				pVar->value = res;
				pVar->valid = 1;
			}
		}
		else
		{
			printf("unknown variable: %s\n", pn->text);
			err = 1;
			res = 0;
		}
		break;
	case IntDeclaration:
		pVar = VariablesFind(vars, pn->text);
		if (pVar != NULL)
		{
			printf("Variable %s has been declared\r\n", pn->text);
			err = 1;
			res = 0;
		}
		else
		{
			child1 = pn->firstChild;
			if (child1 != NULL)
			{
				res = evaluate(child1, n + 1);
				if (err == 0)
				{
					VariablesAdd(&vars, pn->text, res, 1);
				}
				else
					res = 0;
			}
			else
			{
				err = 1;
				res = 0;
				VariablesAdd(&vars, pn->text, 0, 0);
			}
		}
		break;
	default:
		break;
	}

	if (n == 1)
	{
		if (pn->type == IntDeclaration || pn->type == AssignmentStmt)
		{
			if (err == 0)
				printf("%s : %d\n", pn->text, res);
		}
		else if (pn->type != Program)
		{
			if (err == 0)
				printf("%d\n", res);
		}
	}

	return res;
}

void REPL(int verbose)
{
	char str[256];
	int len = 0;
	AST t;
	char *pres;

	vars = NULL;

	if (verbose)
		printf("verbose mode\r\n");
	printf("Simple script language!\r\n");

	printf("\n> ");
	while (1)
	{
		pres = gets(str + len); //ÊäÈëEOF£¨Ctrl+C£©½áÊø³ÌÐò
		if (pres == NULL)
			break;

		len = strlen(str);
		if (str[len - 1] == ';')
		{
			t = parser(str);
			if (t != NULL)
			{
				if (verbose)
				{
					printf("++++++++\r\n");
					ASTPrint(t, 2);
					printf("++++++++\r\n");
				}
				evaluate(t, 0);
				ASTDelete(t);
			}
			else
			{
				printf("\n--------wrong sytax\n");
			}
			len = 0;
			printf("\n> ");
		}
	}
}
