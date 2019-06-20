#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
int main(int argc, char**argv){
    if(argc != 3){
         fprintf(stderr, "usage: %s file ... file ...\n", argv[0]);
	 return (1);
    }
    else{
        //char*first_file;
	struct stat statbuf1;
	struct stat statbuf2;
	if(stat(argv[1], &statbuf1)){
	fprintf(stderr, "usage: %s file ...\n", argv[0]);
	return(1);
	}
	if(stat(argv[2], &statbuf2)){
	fprintf(stderr, "usage: %s file ...\n", argv[0]);
	return(1);	
	}
	printf("%ld\n", (long)(statbuf2.st_mtime - statbuf1.st_mtime));
	return 0;
    }
}
