#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
int main(){
struct stat statbuf1;
struct dirent *p;
char file_name[3] = {'.', '\0'};
char parent_dir[] = {'.', '.', '\0'};
DIR *dp;
long current_ino;
if(lstat(file_name, &statbuf1)!=1){
current_ino = statbuf1.st_ino;
printf("%ld\n", current_ino);
}
if(chdir(parent_dir)!=1){
dp = opendir(file_name);
if(dp != NULL){
while((p=readdir(dp))){
if((p->d_ino == current_ino)){
printf("%s\n", p->d_name);
}
}
closedir(dp);
}
}
return 0;
}
