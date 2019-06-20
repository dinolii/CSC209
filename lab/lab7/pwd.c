#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
int main(){
struct stat statbuf1;
struct dirent *p;
char file_name []= {'.', '\0'};
char parent_dir[] = {'.', '.', '\0'};
DIR *dp;
long current_ino;
if(lstat(file_name, &statbuf1)!=1){
    current_ino = statbuf1.st_ino;
    printf("The current inode is %ld\n", current_ino);
}
else{
    // Write error
    return 1;
}
// Change directory to parent directory
// Loop over every node in the parent directory to find the corresponding directory
while(chdir(parent_dir)!=1 && statbuf1.st_ino != 2){
    // Change back to parent dir
    dp = opendir(file_name);
    if(dp != NULL){
        // Open everything in the parent directory
        while((p=readdir(dp))){
            // If find the thing we want print its name
            if((p->d_ino == current_ino)){
                printf("%s\n", p->d_name);
            }
        }
        closedir(dp);
	// Get info of parent directory and change back to grandparent directory
        lstat(file_name, &statbuf1);
	current_ino = statbuf1.st_ino;
	printf("%ld\n", current_ino);
    }
    else{
    //Write error
    return 1;
    }
}
lstat(file_name, &statbuf1);
printf("%ld\n", statbuf1.st_ino);
dp = opendir(file_name);
if(dp != NULL){
while((p = readdir(dp))){
	printf("%ld\n", p->d_ino);
        printf("%s\n", p->d_name);
}
}
closedir(dp);
return 0;
}
