#include "parser.h"
#include "lexer.h"
#include "token.h"
#include "ast.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


static int additiveMatch(Tokens tokens, AST *pt);

static int primaryMatch(Tokens tokens, AST *pt)
{
	int ret;
	Token token;
	ASTNode *pn;

	ret = TokensPeek(tokens, &token);
	if (ret == 1)
	{
		if (token.type == IntLiteral)
		{
			(void)TokensTake(tokens, &token);
			pn = ASTNodeCreate(tIntLiteral, token.text);
			if (pn != NULL)
			{
				*pt = pn;
				return 1;
			}
			else
			{
				printf("memory error\r\n");
				return 0;
			}
		}
		else if (token.type == Identifier)
		{
			(void)TokensTake(tokens, &token);
			pn = ASTNodeCreate(tIdentifier, token.text);
			if (pn != NULL)
			{
				*pt = pn;
				return 1;
			}
			else
			{
				printf("memory error\r\n");
				return 0;
			}
		}
		else if (token.type == LeftParen)
		{
			(void)TokensTake(tokens, &token);
			ret = additiveMatch(tokens, &pn);
			if (ret == 1)
			{
				ret = TokensPeek(tokens, &token);
				if (ret == 1 && token.type == RightParen)
				{
					(void)TokensTake(tokens, &token);
					*pt = pn;
					return 1;
				}
				else
				{
					printf("expecting right parenthesis\r\n");
					*pt = NULL;
					ASTDelete(pn);
					return 0;
				}
			}
			else
			{
				printf("expecting an additive expression inside parenthesis\r\n");
				return 0;
			}
		}
		else
		{
			printf("primaryMatch: error\r\n");
			return 0;
		}
	}
	else
	{
		printf("primaryMatch: error\r\n");
		return 0;
	}
}

static int multiplicativeMatch(Tokens tokens, AST *pt)
{
	/*
	// resurcive desent  右递归，避免无限递归，但是会出现同一运算符的结合性问题
	ASTNode *child1, *child2, *pn;
	Token token;
	int ret;

	ret = primaryMatch(ps, &child1);
	if (ret == 1)
	{
		ret = TokensPeek(ps, &token);
		if (ret == 1 && (token.type == Star || token.type == Slash))
		{
			(void)TokensTake(ps, &token);
			ret = multiplicativeMatch(ps, &child2);
			if (ret == 1)
			{
				pn = ASTNodeCreate(Multiplicative, token.text);
				if (pn != NULL)
				{
					ASTAddChild(pn, child1);
					ASTAddChild(pn, child2);
					*pt = pn;
					return 1;
				}
				else
				{
					printf("memory error\r\n");
					ASTDelete(child1);
					ASTDelete(child2);
					return 0;
				}
			}
			else
			{
				printf("invalid multiplicative expression, expecting the right part.\r\n");
				ASTDelete(child1);
				return 0;
			}
		}
		else
		{
			*ppn = child1;
			return 1;
		}
	}
	else
	{
		printf("multiplicativeMatch: primaryMatch error\r\n");
		return 0;
	}
	*/

	// 使用ENBF文法描述语法，可用迭代实现语法判断
	ASTNode *child1, *child2, *pn;
	Token token;
	int ret;

	ret = primaryMatch(tokens, &child1);
	if (ret == 1)
	{
		pn = child1;
		while (1)
		{
			ret = TokensPeek(tokens, &token);
			if (ret == 1 && (token.type == Star || token.type == Slash))
			{
				(void)TokensTake(tokens, &token);
				ret = primaryMatch(tokens, &child2);
				if (ret == 1)
				{
					pn = ASTNodeCreate(Multiplicative, token.text);
					if (pn != NULL)
					{
						ASTAddChild(pn, child1);
						ASTAddChild(pn, child2);
						child1 = pn;
					}
					else
					{
						printf("memory error\r\n");
						ASTDelete(child1);
						ASTDelete(child2);
						return 0;
					}
				}
				else
				{
					printf("invalid multiplicative expression, expecting the right part.\r\n");
					ASTDelete(child1);
					return 0;
				}
			}
			else
				break;
		}
		*pt = child1;
		return 1;
	}
	else
	{
		printf("multiplicativeMatch: primaryMatch error\r\n");
		return 0;
	}
}

static int additiveMatch(Tokens tokens, AST *pt)
{
	/*
	// resurcive desent  右递归，避免无限递归，但是会出现同一运算符的结合性问题
	ASTNode *child1, *child2, *pn;
	Token token;
	int ret;

	ret = multiplicativeMatch(tokens, &child1);
	if (ret == 1)
	{
		ret = TokensPeek(tokens, &token);
		if (ret == 1 && (token.type == Plus || token.type == Minus))
		{
			(void)TokensTake(tokens, &token);
			ret = additiveMatch(tokens, &child2);
			if (ret == 1)
			{
				pn = ASTNodeCreate(Additive, token.text, token.len);
				if (pn != NULL)
				{
					ASTNodeAdd(pn, child1);
					ASTNodeAdd(pn, child2);
					*pt = pn;
					return 1;
				}
				else
				{
					printf("memory error\r\n");
					ASTDelete(child1);
					ASTDelete(child2);
					return 0;
				}
			}
			else
			{
				printf("invalid additive expression, expecting the right part.\r\n");
				ASTDelete(child1);
				return 0;
			}
		}
		else
		{
			*pt = child1;
			return 1;
		}
	}
	else
	{
		printf("additiveMatch: multiplicativeMatch error\r\n");
		return 0;
	}
	*/

	// 使用ENBF文法描述语法，可用迭代实现判断
	ASTNode *child1, *child2, *pn;
	Token token;
	int ret;

	ret = multiplicativeMatch(tokens, &child1);
	if (ret == 1)
	{
		pn = child1;
		while (1)
		{
			ret = TokensPeek(tokens, &token);
			if (ret == 1 && (token.type == Plus || token.type == Minus))
			{
				(void)TokensTake(tokens, &token);
				ret = multiplicativeMatch(tokens, &child2);
				if (ret == 1)
				{
					pn = ASTNodeCreate(Additive, token.text);
					if (pn != NULL)
					{
						ASTAddChild(pn, child1);
						ASTAddChild(pn, child2);
						child1 = pn;
					}
					else
					{
						printf("memory error\r\n");
						ASTDelete(child1);
						ASTDelete(child2);
						return 0;
					}
				}
				else
				{
					printf("invalid additive expression, expecting the right part.\r\n");
					ASTDelete(child1);
					return 0;
				}
			}
			else
				break;
		}
		*pt = child1;
		return 1;
	}
	else
	{
		printf("additiveMatch: multiplicativeMatch error\r\n");
		return 0;
	}
}

static int intDeclareMatch(Tokens tokens, AST *pt)
{
	ASTNode *pn = NULL;
	ASTNode *child = NULL;
	Token token;
	int ret;

	ret = TokensPeek(tokens, &token);
	if (ret == 1 && token.type == Int)
	{
		(void)TokensTake(tokens, &token);
		ret = TokensPeek(tokens, &token);
		if (ret == 1 && token.type == Identifier)
		{
			(void)TokensTake(tokens, &token);
			pn = ASTNodeCreate(IntDeclaration, token.text);
			if (pn != NULL)
			{
				ret = TokensPeek(tokens, &token);
				if (ret == 1 && token.type == Assignment)
				{
					(void)TokensTake(tokens, &token);
					ret = additiveMatch(tokens, &child);
					if (ret == 1)
					{
						ASTAddChild(pn, child);
					}
					else
					{
						printf("invalide variable initialization, expecting an expression\r\n");
						ASTDelete(pn);
						return -1;
					}
				}
			}
			else
			{
				printf("memory error\r\n");
				return -1;
			}
		}
		else
		{
			printf("variable name expected\r\n");
			return -1;
		}
	}

	if (pn != NULL)
	{
		ret = TokensPeek(tokens, &token);
		if (ret == 1 && token.type == Semicolon)
		{
			(void)TokensTake(tokens, &token);
		}
		else
		{
			printf("invalid statement, expecting semicolon\r\n");
			ASTDelete(pn);
			return -1;
		}
	}

	*pt = pn;
	if (pn == NULL)
		return 0;
	else
		return 1;
}

static int assignmentStatementMatch(Tokens tokens, AST *pt)
{
	ASTNode *pn = NULL;
	ASTNode *child = NULL;
	Token token, tmpToken;
	int ret;

	ret = TokensPeek(tokens, &token);
	if (ret == 1 && token.type == Identifier)
	{
		(void)TokensTake(tokens, &token);
		tmpToken = token; //保留token，以防将来要用到这个token
		ret = TokensPeek(tokens, &token);
		if (ret == 1 && token.type == Assignment)
		{
			(void)TokensTake(tokens, &token);
			ret = additiveMatch(tokens, &child);
			if (ret == 1)
			{
				pn = ASTNodeCreate(AssignmentStmt, tmpToken.text);
				if (pn != NULL)
				{
					ASTAddChild(pn, child);
					ret = TokensPeek(tokens, &token);
					if (ret == 1 && token.type == Semicolon)
					{
						(void)TokensTake(tokens, &token);
						*pt = pn;
						return 1;
					}
					else
					{
						printf("invalid statement, expecting semicolon\r\n");
						ASTDelete(pn);
						return -1;
					}
				}
				else
				{
					printf("memory error\r\n");
					ASTDelete(child);
					return -1;
				}
			}
			else
			{
				printf("invalide assignment statement, expecting an expression\r\n");
				return -1;
			}
		}
		else
		{
			(void)TokensUntake(tokens);
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

static int expressionStatementMatch(Tokens tokens, AST *pt)
{
	Token *org;
	Token token;
	ASTNode *pn;
	int ret;

	org = TokensGetPos(tokens);

	ret = additiveMatch(tokens, &pn);
	if (ret == 1)
	{
		ret = TokensPeek(tokens, &token);
		if (ret == 1 && token.type == Semicolon)
		{
			(void)TokensTake(tokens, &token);
			*pt = pn;
			return 1;
		}
		else
		{
			//printf("invalid statement, expecting semicolon\r\n");
			TokensSetPos(tokens, org);
			ASTDelete(pn);
			return 0;
		}
	}
	else
	{
		TokensSetPos(tokens, org);
		return 0;
	}
}


AST parser(char *str)
{
	Tokens tokens = NULL;
	AST head;
	AST child;
	int ret;
	int ok = 1;

	tokens = lexer(str);
	//TokensPrint(tokens);
	if (tokens != NULL)
	{
		head = ASTCreate();
		if (head != NULL)
		{
			while (!TokensIsEmpty(tokens))
			{
				ret = intDeclareMatch(tokens, &child);
				if (ret == -1)
				{
					ok = 0;
					break;
				}

				if (ret == 0)
				{
					ret = expressionStatementMatch(tokens, &child);
					if (ret == -1)
					{
						ok = 0;
						break;
					}
				}
				if (ret == 0)
				{
					ret = assignmentStatementMatch(tokens, &child);
					if (ret == -1)
					{
						ok = 0;
						break;
					}
				}

				if (ret == 1)
				{
					ASTAddChild(head, child);
				}
				else
				{
					printf("unknown statement\r\n");
					break;
				}
			}
			TokensDelete(tokens);
			if (ok == 0)
			{
				ASTDelete(head);
				head = NULL;
			}
			return head;
		}
		else
		{
			TokensDelete(tokens);
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}
