#include <stdio.h>
#include <stdlib.h>

#define SIZE 1

int main()
{
    char *p, *result[SIZE];
    int i, n;
    extern int parsepath(char *path, char **result, int size);

    if ((p = getenv("PATH")) == NULL) {
	fprintf(stderr, "testparsepath: PATH variable not found\n");
	return(1);
    }
    p = "::bar";
    if ((n = parsepath(p, result, SIZE)) < 0) {
	fprintf(stderr, "testparsepath: PATH parsing failed (too big?)\n");
	return(1);
    }

    for (i = 0; i < n; i++)
	printf("%s\n", result[i]);

    return(0);
}
