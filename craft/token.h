#ifndef  __TOKEN_H
#define  __TOKEN_H

#include <stdint.h>


typedef enum tokenType {
	None,
	Identifier,
	IntLiteral,
	Int,
	Assignment,
	GT, GE,
	Plus, Minus, Star, Slash,
	Semicolon, LeftParen, RightParen,
} TokenType;

typedef struct token {
	struct token *prev;
	struct token *next;
	TokenType type;
	char text[64]; //token�ĳ��Ȳ��ܳ���63
	uint8_t len;
} Token;

struct tokenGrp {
	struct token *head;
	struct token *tail;
	struct token *iter;
	uint32_t len;  //token�б�ĳ��Ȳ��ܳ���uint32_t��ʾ�ķ�Χ
};
typedef struct tokenGrp * Tokens;


Tokens TokensCreate(void);
void TokensDelete(Tokens tokens);
int TokensPut(Tokens tokens, Token token);
int TokensTake(Tokens tokens, Token *pToken);
int TokensPeek(Tokens tokens, Token *pToken);
int TokensUntake(Tokens tokens);
int TokensIsEmpty(Tokens tokens);
void TokensPrint(Tokens tokens);
Token *TokensGetPos(Tokens tokens);
void TokensSetPos(Tokens tokens, Token *pToken);

#endif
