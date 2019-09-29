#include "token.h"
#include "lexer.h"
#include "simpleScript.h"
#include <string.h>


int main(int argc, char *argv[])
{
	/*
	// lexer ²âÊÔ
	Tokens tokens;
	char str[128] = "int a=10 age >= 45 2+3*5 3 / 6 inta=3 (a=b);1";

	tokens = lexer(str);
	TokensPrint(tokens);
	TokensDelete(tokens);
	*/

	int verbose = 0;

	if (argc > 0 && strcmp(argv[0], "-v") == 0)
		verbose = 1;
	else
		verbose = 0;

	REPL(verbose);
}