#include <stdio.h>
#include <unistd.h>

int main()
{
    int pipefd[2];

    if (pipe(pipefd)) {
        perror("pipe");
        return(1);
    }
    switch (fork()) {
    case -1:
        perror("fork");
        return(1);
    case 0:
        /* child */
        printf("I am the child.  FEED ME\n");
        char buf[20];
        // TODO: read into buf from the pipe, terminating the string based on
        //       how many bytes read() says we read
        read(pipefd[0], buf, 19);
        printf("Parent says '%s'\n", buf);
        return(0);
    default:
        /* parent */
        printf("I am the parent.  Have some data.\n");
        // TODO: write a string into the pipe.  Do not write any extra
        //       bytes (such as a '\0')
        write(pipefd[1], "hello", 20);
        printf("Ok, sent some data.  Hope the child likes it.\n");
        return(0);
    }
}
