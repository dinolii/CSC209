#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[100];
    int i;

    //gets(s);
    if(fgets(s, 100, stdin) == NULL){
	perror("fgets");
        exit(1);
    }
    if ((i = atoi(s)) == 12)
        printf("do something\n");
    printf("in any case, do something else\n");
    return(0);
}
