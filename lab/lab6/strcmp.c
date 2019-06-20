#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
	fprintf(stderr, "usage: %s string1 string2\n", argv[0]);
	return(1);
    }

    printf("strcmp(\"%s\",\"%s\") returns %d\n", argv[1], argv[2],
	    strcmp(argv[1], argv[2]));
    return(0);
}
