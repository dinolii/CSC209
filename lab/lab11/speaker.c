#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "wordlist.h"
#include "anagramlist.h"
extern int wordlistsize;
int main(){
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd < 0){
        perror("/dev/urandom");
        exit(1);
    }
    else{
        unsigned char r;
        for(int i = 0; i < 10; i++){
            int temp = read(fd, &r, 1);
            if(temp < 0){
                perror("open");
                exit(1);
            }
            else if(temp == 1){
		r = (r % wordlistsize);
                setbuf(stdout, NULL);	
		printf("%s\n", wordlist[r]);
            }
            sleep(1);
        }
    }
}
