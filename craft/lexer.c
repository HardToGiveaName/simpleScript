#include "lexer.h"
#include <string.h>
#include <stdio.h>


typedef enum state {
	stateNone,
	stateIdentifier,
	stateGT,
	stateGE,
	stateIntLiteral,
	stateInt1,
	stateInt2,
	stateInt3,
	stateInt,
	stateAssignment,
	statePlus,
	stateMinus,
	stateStar,
	stateSlash,
	stateSemicolon,
	stateLeftParen,
	stateRightParen,
} State;


static int isAlpha(char c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return 1;
	return 0;
}

static int isDigit(char c)
{
	if ('0' <= c && c <= '9')
		return 1;
	return 0;
}

static TokenType stateToType(State state)
{
	TokenType type;

	switch (state)
	{
	case stateIdentifier:
		type = Identifier;
		break;
	case stateGT:
		type = GT;
		break;
	case stateGE:
		type = GE;
		break;
	case stateIntLiteral:
		type = IntLiteral;
		break;
	case stateInt1:
		type = Identifier;
		break;
	case stateInt2:
		type = Identifier;
		break;
	case stateInt3:
		type = Int;
		break;
	case stateInt:
		type = Int;
		break;
	case stateAssignment:
		type = Assignment;
		break;
	case statePlus:
		type = Plus;
		break;
	case stateMinus:
		type = Minus;
		break;
	case stateStar:
		type = Star;
		break;
	case stateSlash:
		type = Slash;
		break;
	case stateSemicolon:
		type = Semicolon;
		break;
	case stateLeftParen:
		type = LeftParen;
		break;
	case stateRightParen:
		type = RightParen;
		break;
	default:
		type = None;
		break;
	}
	return type;
}


Tokens lexer(char *str)
{
	Token token;
	Tokens tokens;
	uint64_t i; //做词法解析的文本长度不能超过uint64_t类型的最大长度
	char c;
	State state;
	int ret;

	tokens = TokensCreate();
	state = stateNone;
	i = 0;
	strcpy(token.text, "");
	token.len = 0;

	while (str[i] != '\0')
	{
		c = str[i];
		switch (state)
		{
		case stateNone:
			if (isAlpha(c))
			{
				if (c == 'i')
					state = stateInt1;
				else
					state = stateIdentifier;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (isDigit(c))
			{
				state = stateIntLiteral;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '>')
			{
				state = stateGT;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '=')
			{
				state = stateAssignment;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '+')
			{
				state = statePlus;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '-')
			{
				state = stateMinus;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '*')
			{
				state = stateStar;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '/')
			{
				state = stateSlash;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == ';')
			{
				state = stateSemicolon;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == '(')
			{
				state = stateLeftParen;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			else if (c == ')')
			{
				state = stateRightParen;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			i++;
			break;
		case stateIdentifier:
			if (isAlpha(c) || isDigit(c))
			{
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				token.type = Identifier;
				ret = TokensPut(tokens, token);
				if (ret == 1)
				{
					state = stateNone;
					token.type = None;
					strcpy(token.text, "");
					token.len = 0;
				}
				else
				{
					printf("memory error\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			break;
		case stateGT:
			if (c == '=')
			{
				state = stateGE;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				token.type = GT;
				ret = TokensPut(tokens, token);
				if (ret == 1)
				{
					state = stateNone;
					token.type = None;
					strcpy(token.text, "");
					token.len = 0;
				}
				else
				{
					printf("memory error\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			break;
		case stateIntLiteral:
			if (isDigit(c))
			{
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				token.type = IntLiteral;
				ret = TokensPut(tokens, token);
				if (ret == 1)
				{
					state = stateNone;
					token.type = None;
					strcpy(token.text, "");
					token.len = 0;
				}
				else
				{
					printf("memory error\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			break;
		case stateInt1:
			if (c == 'n')
			{
				state = stateInt2;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else if (isAlpha(c) || isDigit(c))
			{
				state = stateIdentifier;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				token.type = Identifier;
				ret = TokensPut(tokens, token);
				if (ret == 1)
				{
					state = stateNone;
					token.type = None;
					strcpy(token.text, "");
					token.len = 0;
				}
				else
				{
					printf("memory error\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			break;
		case stateInt2:
			if (c == 't')
			{
				state = stateInt3;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else if (isAlpha(c) || isDigit(c))
			{
				state = stateIdentifier;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				token.type = Identifier;
				ret = TokensPut(tokens, token);
				if (ret == 1)
				{
					state = stateNone;
					token.type = None;
					strcpy(token.text, "");
					token.len = 0;
				}
				else
				{
					printf("memory error\r\n");
					TokensDelete(tokens);
					return NULL;
				}
			}
			break;
		case stateInt3:
			if (c == ' ')
			{
				state = stateInt;
			}
			else if (isAlpha(c) || isDigit(c))
			{
				state = stateIdentifier;
				if (token.len < 63)
				{
					token.text[token.len++] = c;
					token.text[token.len] = '\0';
				}
				else
				{
					printf("token length is over 63\r\n");
					TokensDelete(tokens);
					return NULL;
				}
				i++;
			}
			else
			{
				state = stateInt;
			}
			break;
		case stateGE:
		case stateInt:
		case stateAssignment:
		case statePlus:
		case stateMinus:
		case stateStar:
		case stateSlash:
		case stateSemicolon:
		case stateLeftParen:
		case stateRightParen:
			token.type = stateToType(state);
			ret = TokensPut(tokens, token);
			if (ret == 1)
			{
				state = stateNone;
				token.type = None;
				strcpy(token.text, "");
				token.len = 0;
			}
			else
			{
				printf("memory error\r\n");
				TokensDelete(tokens);
				return NULL;
			}
			break;
		default:
			break;
		}
	}
	if (state != stateNone)
	{
		token.type = stateToType(state);
		ret = TokensPut(tokens, token);
		if (ret == 1)
		{
			state = stateNone;
			token.type = None;
			strcpy(token.text, "");
			token.len = 0;
		}
		else
		{
			printf("memory error\r\n");
			TokensDelete(tokens);
			return NULL;
		}
	}

	return tokens;
}
