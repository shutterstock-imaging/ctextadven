#include <stdbool.h>
#include <stdio.h>
#include "parsexec.h"
#include "parsexec.c"

static char input[100] = "look around";

static bool getInput(void)
{
	printf("\n> ");
	return fgets(input, sizeof input, stdin) != NULL;
}

int main()
{
	printf("Welcome to ctextadven indev\n");
	while (parseAndExecute(input) && getInput());
	printf("\nGoodbye.\n");
	return 0;
}
