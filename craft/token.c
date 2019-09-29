#include "token.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


Tokens TokensCreate(void)
{
	Tokens tokens;

	tokens = (Tokens)malloc(sizeof(struct tokenGrp));
	if (tokens != NULL)
	{
		tokens->head = tokens->tail = NULL;
		tokens->iter = NULL;
		tokens->len = 0;
	}

	return tokens;
}

void TokensDelete(Tokens tokens)
{
	Token *p, *pt;

	if (tokens == NULL)
		return;

	p = tokens->head;
	while (p != NULL)
	{
		pt = p->next;
		free(p);
		p = pt;
	}
	free(tokens);
}

int TokensPut(Tokens tokens, Token token)
{
	Token *pt;

	if (tokens == NULL)
		return -1;

	pt = (Token *)malloc(sizeof(Token));
	if (pt == NULL)
		return 0;

	*pt = token;
	pt->prev = NULL;
	pt->next = NULL;

	if (tokens->len == 0)
	{
		tokens->head = tokens->tail = pt;
	}
	else
	{
		tokens->tail->next = pt;
		pt->prev = tokens->tail;
		tokens->tail = pt;
	}
	tokens->len++;

	if (tokens->iter == NULL)
		tokens->iter = pt;

	return 1;
}

int TokensTake(Tokens tokens, Token *pToken)
{
	if (tokens == NULL)
		return -1;
	
	if (tokens->iter == NULL)
		return 0;

	*pToken = *(tokens->iter);
	tokens->iter = tokens->iter->next;

	return 1;
}

int TokensPeek(Tokens tokens, Token *pToken)
{
	if (tokens == NULL)
		return -1;

	if (tokens->iter == NULL)
		return 0;

	*pToken = *(tokens->iter);

	return 1;
}

int TokensUntake(Tokens tokens)
{
	if (tokens == NULL)
		return -1;

	if (tokens->iter == NULL)
		return 0;

	tokens->iter = tokens->iter->prev;

	return 1;
}

static void print_a_token(Token token)
{
	switch (token.type)
	{
	case Identifier:
		printf("Identifier\t");
		break;
	case GT:
		printf("GT\t\t");
		break;
	case GE:
		printf("GE\t\t");
		break;
	case IntLiteral:
		printf("IntLiteral\t");
		break;
	case Int:
		printf("Int\t\t");
		break;
	case Assignment:
		printf("Assignment\t");
		break;
	case Plus:
		printf("Plus\t\t");
		break;
	case Minus:
		printf("Minus\t\t");
		break;
	case Star:
		printf("Star\t\t");
		break;
	case Slash:
		printf("Slash\t\t");
		break;
	case Semicolon:
		printf("Semicolon\t");
		break;
	case LeftParen:
		printf("LeftParen\t");
		break;
	case RightParen:
		printf("RightParen\t");
		break;
	default:
		printf("Unknown type\t");
		break;
	}
	printf("%s\r\n", token.text);
}

void TokensPrint(Tokens tokens)
{
	Token *pt;

	if (tokens == NULL)
		return;

	pt = tokens->head;
	while (pt != NULL)
	{
		print_a_token(*pt);
		pt = pt->next;
	}
}

int TokensIsEmpty(Tokens tokens)
{
	if (tokens == NULL)
		return -1;

	if (tokens->iter == NULL)
		return 1;
	return 0;
}

Token *TokensGetPos(Tokens tokens)
{
	if (tokens == NULL)
		return NULL;

	return tokens->iter;
}

void TokensSetPos(Tokens tokens, Token *pToken)
{
	if (tokens == NULL)
		return;

	tokens->iter = pToken;
}
