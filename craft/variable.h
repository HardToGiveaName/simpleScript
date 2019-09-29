#ifndef __VARIABLE_H
#define __VARIABLE_H


typedef struct variable {
	struct variable *next;
	char text[64]; //变量名长度不能超过63
	int len;
	int value;
	int valid;
} Variable;
typedef struct variable * Variables;


int VariablesAdd(Variables *vs, char *text, int value, int valid);
Variable *VariablesFind(Variables vs, char *text);
int VariableIsValid(Variable *pVar);

#endif
