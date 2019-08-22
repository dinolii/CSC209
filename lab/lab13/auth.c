#include <stdio.h>
#include <string.h>

int main()
{
    extern int authenticate();
    if (authenticate() != 1) {
        printf("Login incorrect.\n");
        return(1);
    }
    printf("Access to secret stuff achieved\n");
    return(0);
}


int authenticate()
{
    char buf[80];
    printf("Password: ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return(0);
    else if (strcmp(buf, "sesame\n") == 0)
        return(1);
    else
        return(2);
}
