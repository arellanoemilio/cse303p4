#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"support.h"

/* hello() - print some output so we know the shared object loaded.
 *
 * The function signature takes an untyped parameter, and returns an untyped
 * parameter. In this way, the signature *could* support any behavior, by
 * passing in a struct and returning a struct. */
void *hello(void *input)
{
	printf("hello from a .so\n");
	return NULL;
}

void myToUpper(char *dest, char *orig){
	for(int i = 0; i < strlen(orig)+1; i++){
		dest[i] = toupper(orig[i]);
	}
}

void *ucase(void *input)
{
	struct team_t inTeam = (struct team_t *)input;
	struct team_t *team = (struct team_t *) malloc(sizeof(struct team_t));
	team->name1 = (char *)malloc((strlen(inTeam->name1) + 1) *sizeof(char));
	team->name2 = (char *)malloc((strlen(inTeam->name2) + 1) *sizeof(char));
	team->name3 = (char *)malloc((strlen(inTeam->name3) + 1) *sizeof(char));
	team->email1 = (char *)malloc((strlen(inTeam->email1) + 1) *sizeof(char));
	team->email2 = (char *)malloc((strlen(inTeam->email2) + 1) *sizeof(char));
	team->email3 = (char *)malloc((strlen(inTeam->email3) + 1) *sizeof(char));
	myToUpper(team->name1, inTeam->name1);
	myToUpper(team->name2, inTeam->name2);
	myToUpper(team->name3, inTeam->name3);
	myToUpper(team->email1, inTeam->email1);
	myToUpper(team->email2, inTeam->email2);
	myToUpper(team->email3, inTeam->email3);

	return (void *)team;
}
