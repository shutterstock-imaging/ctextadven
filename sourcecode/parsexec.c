#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "location.h"
#include "location.c"

bool parseAndExecute(char *input)
{
	char *verb = strtok(input, " \n");
	char *noun = strtok(NULL, " \n");
	if (verb != NULL)
	{
		if (strcmp(verb, "quit") == 0)
		{
			return false;
		}
		else if (strcmp(verb, "look") == 0)
		{
			executeLook(noun);
		}
		else if (strcmp(verb, "go") == 0)
		{
			executeGo(noun);
		}
		else if (strcmp(verb, "help")== 0)
		{
			printf("The current commands are look, quit, go and help. more will information here will appear soon, current locations are go and field.");
		}		
		else
		{
			printf("I don't know how to '%s'. \n", verb);
		}
	}
	return true;
}

