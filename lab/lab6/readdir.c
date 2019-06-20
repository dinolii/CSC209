#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *dp;
    struct dirent *p;

    if ((dp = opendir(".")) == NULL) {
	perror(".");
	return(1);
    }
    while ((p = readdir(dp)))
	printf("%s\n", p->d_name);
    closedir(dp);

    return(0);
}
