#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int c, port = 1234, status = 0;
    int fd, clientfd;
    socklen_t size;
    struct sockaddr_in r, q;

    while ((c = getopt(argc, argv, "p:")) != EOF) {
        switch (c) {
        case 'p':
            port = atoi(optarg);
            break;
        default:
            status = 1;
        }
    }
    if (status || optind < argc) {
        fprintf(stderr, "usage: %s [-p port]\n", argv[0]);
        return(1);
    }

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return(1);
    }

    memset(&r, '\0', sizeof r);
    r.sin_family = AF_INET;
    r.sin_addr.s_addr = INADDR_ANY;
    r.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&r, sizeof r) < 0) {
        perror("bind");
        return(1);
    }
    if (listen(fd, 5)) {
        perror("listen");
        return(1);
    }
