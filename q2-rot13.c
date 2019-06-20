#include <stdio.h>

int main()
{
    int c;
    while ((c = getchar()) != EOF) {
	if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
	    putchar(c + 13);
	else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
	    putchar(c - 13);
	else
	    putchar(c);
    }
    return(0);
}
