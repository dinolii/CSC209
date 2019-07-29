#include <stdio.h>
#include <string.h>
#include "anagramlist.h"

extern void makesorted();
extern char *anagram(char *s);
extern void sortletters(char *s);


int main()
{
    char buf[80], *p, *ana;

    makesorted();
    while (fgets(buf, sizeof buf, stdin)) {
	if ((p = strchr(buf, '\n')))
	    *p = '\0';
	ana = anagram(buf);
	printf("You say %s; ", buf);
	if (ana)
	    printf("I say %s\n", ana);
	else
	    printf("I am speechless\n");
    }
    return(0);
}


void makesorted()
{
    int i;
    for (i = 0; i < anagramlistsize; i++) {
	strcpy(anagramlist[i].sorted, anagramlist[i].word);
	sortletters(anagramlist[i].sorted);
    }
}

char *anagram(char *s)
{
    int i;
    char sorted[80];
    strncpy(sorted, s, sizeof sorted);
    sorted[sizeof sorted - 1] = '\0';
    sortletters(sorted);

    for (i = 0;
	    i < anagramlistsize && strcmp(sorted, anagramlist[i].sorted);
	    i++)
	;
    if (i < anagramlistsize)
	return(anagramlist[i].word);
    else
	return(NULL);
}

void sortletters(char *p)
{
    char *q, t;
    for (; *p; p++) {
	for (q = p + 1; *q; q++) {
	    if (*q < *p) {
		t = *q;
		*q = *p;
		*p = t;
	    }
	}
    }
}
