#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv){
    int pid = atoi(argv[1]);
    char temp = *(argv[2]);
    int count = 0;
    while(count < 8){
        if(temp & 128){
            kill(pid, SIGUSR2);
        }
        else{
            kill(pid, SIGUSR1);
        }
        temp <<= 1;
        count ++;
        usleep(100000);
    }
}
