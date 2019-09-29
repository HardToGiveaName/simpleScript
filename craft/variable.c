#include "variable.h"
#include <string.h>
#include <malloc.h>


int VariablesAdd(Variables *vs, char *text, int value, int valid)
{
	Variable *pv, *prev;
	int ok = 0;

	if (*vs == NULL)
	{
		pv = (Variable *)malloc(sizeof(Variable));
		if (pv != NULL)
		{
			pv->next = NULL;
			strcpy(pv->text, text);
			pv->len = strlen(text);
			pv->value = value;
			pv->valid = valid;
		}
		*vs = pv;
		if (pv == NULL)
			return 0;
		else
			return 1;
	}
	else
	{
		prev = NULL;
		pv = *vs;
		while (pv != NULL)
		{
			if (strcmp(pv->text, text) == 0)
			{
				pv->value = value;
				pv->valid = valid;
				ok = 1;
				break;
			}
			prev = pv;
			pv = pv->next;
		}
		if (ok == 0)
		{
			pv = (Variable *)malloc(sizeof(Variable));
			if (pv != NULL)
			{
				pv->next = NULL;
				strcpy(pv->text, text);
				pv->len = strlen(text);
				pv->value = value;
				pv->valid = valid;
			}
			prev->next = pv;
			if (pv == NULL)
				return 0;
			else
				return 1;
		}
		else
			return 1;
	}
}

Variable *VariablesFind(Variables vs, char *text)
{
	Variable *pv = vs;

	while (pv != NULL)
	{
		if (strcmp(pv->text, text) == 0)
			break;
		pv = pv->next;
	}
	return pv;
}

int VariableIsValid(Variable *pVar)
{
	return pVar->valid;
}
