#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int count = 0;
int sig = 0;
void receive_signal(int signal){
    sig <<= 1;
    if(signal == SIGUSR2){
        sig += 1;
    }
    count += 1;
    if(count == 8){
        printf("%c\n", sig);
        exit(0);
    }
}

int main(){
    printf("%d\n", getpid());
    signal(SIGUSR1, receive_signal);
    signal(SIGUSR2, receive_signal);
    while(1);
    return 0;
}
