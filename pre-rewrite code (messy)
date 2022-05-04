#include <stdbool.h>
#include <stdio.h>
#include <string.h> 


extern bool parseAndExecute(char *input);
extern void executeLook(const char *noun);
extern void executeGo(const char *noun);
extern void executeGet(const char *noun);
extern void executeDrop(const char *noun);
extern void executeAsk(const char *noun);
extern void executeGive(const char *noun);
extern void executeInventory(void);

typedef struct object {
	const char *description;
	const char *tag;
	struct object *location;
} OBJECT;

extern OBJECT objs[];

#define field	(objs + 0)
#define cave	(objs + 1)
#define silver  (objs + 2)
#define gold	(objs + 3)
#define guard	(objs + 4)
#define player	(objs + 5)

#define endOfObjs	(objs + 6)


OBJECT objs[] = {
	{"an open field", "field"	, NULL  },
	{"a little cave", "cave"	, NULL  },
	{"a silver coin", "silver"	, field },
	{"a gold coin"	, "gold"	, cave	},
	{"a strong guard", "guard"	, field	},
	{"yourself"	, "yourself"	, field	}
};



static bool objectHasTag(OBJECT *obj, const char *noun)
{
	return noun != NULL && *noun != '\0' && strcmp(noun, obj->tag) == 0;
}

static OBJECT *getObject(const char *noun)
{
	OBJECT *obj, *res = NULL;
	for (obj = objs; obj < endOfObjs; obj++)
	{
		if (objectHasTag(obj, noun))
		{
			res = obj;
		}
	}
	return res;
}

OBJECT *getVisible(const char *intention, const char *noun)
{
	OBJECT *obj = getObject(noun);
	if (obj == NULL)
	{
		printf("I don't understand %s.\n", intention);
	}
	else if (!(obj == player ||
		obj == player->location ||
		obj->location == player ||		
		obj->location == player->location ||
		obj->location == NULL ||
		obj->location->location == player ||
		obj->location->location == player->location))
	{
		printf("You don't see any %s here.\n", noun);
		obj = NULL;
	}
	return obj;
}	
		
OBJECT *getPossession(OBJECT *from, const char *verb, const char *noun)
{
	OBJECT *obj = NULL;
	if (from == NULL)
	{
		printf("I don't understand who you want to %s.\n", verb);
	}
	else if ((obj = getObject(noun)) == NULL)
	{
		printf("I don't understand what you want to %s.\n", verb);
	}
	else if (obj == from)
	{
		printf("You should not be doing that to %s.\n", obj->description);
		obj = NULL;
	}
	else if (obj->location != from)
	{
		if (from == player)
		{
			printf("You are not holding any %s.\n", noun);
		}
		else
		{
			printf("There appears to be no %s you can get from %s.\n", noun, from->description);
		}
		obj = NULL;
	}
	return obj;
}


OBJECT *actorHere(void)
{
	OBJECT *obj;
	for (obj = objs; obj < endOfObjs; obj++)
	{
		if (obj->location == player->location && obj == guard)
		{
			return obj;
		}
	}
	return NULL;
}


int listObjectsAtLocation(OBJECT *location)
{
	int count = 0;
	OBJECT *obj;
	for (obj = objs; obj < endOfObjs; obj++)
	{
		if (obj != player && obj->location == location)
		{
			if (count++ == 0)
			{
				printf("You see:\n");
			}
			printf("%s\n", obj->description);
		}
	}
	return count;
}




void executeGet(const char *noun)
{
	OBJECT *obj = getVisible("what you want to get", noun);
	if (obj == NULL)
	{
		// already handled by getVisible
	}
	else if (obj == player)
	{
		printf("You should not be doing that to yourself.\n");
	}
	else if (obj->location == player)
	{
		printf("You already have %s.\n", obj->description);
	}	
	else if (obj->location == guard)
	{
		printf("You should ask %s nicely.\n", obj->location->description);
	}
	else
	{
		moveObject(obj, player);
	}
}

void executeDrop(const char *noun)
{
	moveObject(getPossession(player, "drop", noun), player->location);
}

void executeAsk(const char *noun)
{
	moveObject(getPossession(actorHere(), "ask", noun), player);
}

void executeGive(const char *noun)
{
	moveObject(getPossession(player, "give", noun), actorHere());
}

void executeInventory(void)
{
	if (listObjectsAtLocation(player) == 0)
	{
		printf("You are empty-handed.\n");
	}
}


static void describeMove(OBJECT *obj, OBJECT *to)
{
	if (to == player->location)
	{
		printf("You drop %s.\n", obj->description);
	}
        else if (to != player)
	{
		printf(to == guard ? "You give %s to %s.\n" : "You put %s in %s.\n", obj->description, to->description);
	}
	else if (obj->location == player->location)
	{
		printf("You pick up %s.\n", obj->description);
	}
	else
	{
		printf("You get %s from %s.\n", obj->description, obj->location->description);
	}
}


void moveObject(OBJECT *obj, OBJECT *to)
{
	if (obj == NULL)
	{
		// already handled by getVisible or getPossession
	}
	else if (to == NULL)
	{
		printf("There is nobody here to give that to.\n");
	}
	else if (obj->location == NULL)
	{
		printf("That is way to too heavy.\n");
	}
	else
	{
		describeMove(obj, to);
		obj->location = to;
	}
}


void executeLook(const char *noun)
{
	if (noun != NULL && strcmp(noun, "around") == 0)
	{
		printf("\nYou are in %s \n", player->location->description);
		listObjectsAtLocation(player->location);
	}
	else
	{
		printf("I don't understand what you want to see.\n");
	}
}


void executeGo(const char *noun)
{
	OBJECT *obj = getVisible("where you want to go", noun);
	if (obj == NULL)
	{
	 // handled by getVisible
	}
	else if (obj->location == NULL && obj != player->location)
	{
		printf("OK.\n");
		player->location = obj;
		executeLook("around");
	}
	else
	{
		printf("You can't get much closer than this.\n");
	}
}

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
		else if (strcmp(verb, "get") == 0)
		{
			executeGet(noun);
		}
		else if (strcmp(verb, "drop") == 0)
		{
			executeDrop(noun);
		}
		else if (strcmp(verb, "give") == 0)
		{
			executeGive(noun);
		}
		else if (strcmp(verb, "ask") == 0)
		{
			executeAsk(noun);
		}
		else if (strcmp(verb, "inventory") == 0)
		{
			executeInventory();
		}
		else 
		{
			printf("I don't know how to do that.\n");
		}
	}
	return true;
}


static char input[100] = "look around";

static bool getInput(void)
{
   printf("\n--> ");
   return fgets(input, sizeof input, stdin) != NULL;
}

int main()
{
   printf("\n(Welcome to Test, The current commands are;\nlook, go, quit, get, ask, give, drop and inventory.)\n");
   printf(" |/		\n");
   printf("    ___\n");
   printf("   (.· |\n");
   printf("   (<> |\n");
   printf("  / __  \\ \n");
   printf(" ( /  \\ /| \n");
   printf("_/\\ __)/_)\n");
   printf("\\/-____\\/\n");
   while (parseAndExecute(input) && getInput());
   printf("\nBye!\n");
   return 0;
}
