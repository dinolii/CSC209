#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
//There are four functions to be used for this program;
// Their headers are defined here
int find_dire(char *file_path);
int find_dire_s(char *file_path, int limit, int *acc);
int find_dire_n(char*file_name, int limit, int* acc);
void fill_path(char *file_path, char *file_name, char *res, int size);
static int sflag = 0, limit = -1;
int main(int argc, char **argv){
    // c indicates the option character
    int c =0;
    // status indicates the exit status
    int status = 0;
    if(argc == 1){
        fprintf(stderr, "usage: funnytimes [-s] [-n limit] dir ...\n");
        return 1;
    }
    else if(argc == 2){
        struct stat statbuf;
        // Handle invalid options
        if (*argv[1] == '-'){
            if(strlen(argv[1]) == 1){
                fprintf(stderr, "%c: No such file or directory\n", '-');
                return 1;
            }
            else if(strlen(argv[1]) > 1){
                char *head = argv[1];
                if ( head[1] == 's'){
                    fprintf(stderr, "usage: funnytimes [-s] [-n limit] dir ...\n");
                    return 1;
                }
                else if( head[1] == 'n'){
                    if(strlen(argv[1]) == 2){
                        fprintf(stderr, "funnytimes: option requires an argument -- 'n'\n");
                        fprintf(stderr, "usage: funnytimes [-s] [-n limit] dir ...\n");
                        return 1;
                    }
                }
                else{
                    fprintf(stderr, "funnytimes: invalid option -- '%s'\n", argv[1]);
                    fprintf(stderr, "usage: funnytimes [-s] [-n limit] dir ...\n");
                    return 1;
                }
            }
        }
        // If given directory cannot be opened
        if(lstat(argv[1], &statbuf)){
            fprintf(stderr, "%s: No such file or directory\n", argv[1]);
            status = 1;
            return 1;
        }
        // If the given directory is correct but that is not a directory
        if(!S_ISDIR(statbuf.st_mode)){
            fprintf(stderr, "%s: Is not a directory\n", argv[1]);
            return 1;
        }
        // Otherwise handle the file
        return find_dire(argv[1]);
    }
    // Otherwise handle multiple options
    while((c = getopt(argc, argv, "n:s")) != EOF){
        switch(c){
        // If there is an option of n 
        // records its argument as limit by atoi
        case 'n':
            limit = atoi(optarg);
            break;
        // If there is an option of s
        // Set the flag to be true
        case 's':
            sflag = 1;
            break;
        // Otherwise record the status as 1
        case '?':
            status = 1;
            break;
        }
    }
    // If there are any invalid options given write to stderr
    if (status == 1){
        fprintf(stderr, "usage: funnytimes [-s] [-n limit] dir ...\n");
        return status;
    }
    // Otherwise process the directory name
    char *file_path = argv[optind];
    int *count = malloc(sizeof(int));
    *count = 0;
    // Based on the sflag and limit to call the proper function
    if(sflag){
        status = find_dire_s(file_path, limit, count);
    }
    else if(sflag == 0 && limit != -1){
        status = find_dire_n(file_path, limit, count);
    }
    return status;
}

// This is the function used to traverse the files with no options
/*
Inputs: file_path is the pointer to the array of char
Outputs: The output for find_dir is the exit status of the function
This function traverse the file tree rooted at the file_path
it prints the directory name if the directory's m_time is differ
than its c_time
*/
int find_dire(char *file_path){
    //Defined proper variables
    int status = 0;
    struct stat statbuf;
    // If the given file cannot be opened
    // Write the error message to stderr and update the status
    if(lstat(file_path, &statbuf)){
        fprintf(stderr, "%s: No such file or directory\n", file_path);
        status = 1;
    }
    // If the given path is a directory
    // Start to process the directory
    if(S_ISDIR(statbuf.st_mode)){
        DIR * dp;
        struct dirent *p;
        // If the directory cannot be opened write to the stderr
        // update the status
        if((dp = opendir(file_path)) == NULL){
            fprintf(stderr, "%s: Permission denied\n", file_path);
            status = 1;
        }
        // Otherwise, do the recursive call on every sub-directory
        else{
            while((p = readdir(dp))){
                // The algorithm should escape . and .. since
                // Doing recursive call on . and .. will raise stack overflow
                if(strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0){
                    // Create an array to hold the sub-dire's name
                    // Calculate the lenght of the sub-directory
                    char *dire_name;
                    int new_dir_len = (strlen(file_path) + 1 +
                        strlen(p->d_name) + 1);
                    // Allocate space for the array of sub-dire 
                    dire_name = malloc(sizeof(char) * new_dir_len);
                    // Call the function to fill the array with sub-dir's name
                    fill_path(file_path, p->d_name, dire_name, new_dir_len);
                    // Try to access the info of sub-dire by using lstat
                    // If there is an error raised write it to stderr
                    struct stat statbuf2;
                    if(lstat(dire_name, &statbuf2)){
                        fprintf(stderr, "%s: No such file or directory\n", dire_name);
                        status = 1;
                    }
                    // Print the sub-dir's name if its mtime != its ctime
                    if(statbuf2.st_mtime != statbuf2.st_ctime){
                        printf("%s\n", dire_name);
                    }
                    // If the recursive call did not raise error
                    // Keep track the status through further recursive call
                    if(status == 0){
                        status = find_dire(dire_name);
                    }
                    // If there is any error raised during the recursive call
                    // Update the status to 1 and keep doing the recursive call
                    else{
                        status = 1;
                        find_dire(dire_name);
                    }
                }
            }
            closedir(dp);
        }
    }
    return status;
}

// This is the function used for the option s
/*
Inputs: file_path is a pointer of char indicates the name of path
limit indicates the limit of the number of directory can be printed out
if limiit is -1 then this indicates there is no restriction on the number
of directory
acc is a pointer to int used to track how many paths have been printed
Output: This function return the exit status
*/
int find_dire_s(char *file_path, int limit, int *acc){
    //Defined proper variables
    int status = 0;
    struct stat statbuf;
    // If the given file cannot be opened
    // Write the error message to stderr and update the status
    if(lstat(file_path, &statbuf)){
        fprintf(stderr, "%s: No such file or directory\n", file_path);
        status = 1;
    }
    // If the given path is a directory
    // Start to process the directory
    if(S_ISDIR(statbuf.st_mode)){
        DIR *dp;
        struct dirent *p;
        // If the directory cannot be opened write to the stderr
        // update the status
        if((dp = opendir(file_path)) == NULL){
            status = 1;
            fprintf(stderr, "%s: Permission denied\n", file_path);
        }
        // Otherwise, do the recursive call on every sub-directory
        else{
            while((p = readdir(dp))){
                // The algorithm should escape . and .. since
                // Doing recursive call on . and .. will raise stack overflow
                if(strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0){
                    // Create an array to hold the sub-dire's name
                    // Calculate the length of the sub-directory
                    char *dire_name;
                    int new_dir_len = (strlen(file_path) + 1 +
                        strlen(p->d_name) + 1);
                    // Allocate space for the array of sub-dire
                    dire_name = malloc(sizeof(char) * new_dir_len);
                    // Call the function to fill the array with sub-dir's name
                    fill_path(file_path, p->d_name, dire_name, new_dir_len);
                    // Try to access the info of sub-dire by using lstat
                    // If there is an error raised write it to stderr
                    struct stat statbuf2;
                    if(lstat(dire_name, &statbuf2)){
                        status = 1;
                        fprintf(stderr, "%s: No such file or directory\n", dire_name);
                    }
                    // If there is restriction on the limit
                    // The algorithm needs to check is the m_time < c_time
                    // As well as how many paths have been printed
                    if(limit != -1){
                        if(statbuf2.st_mtime < statbuf2.st_ctime){
                            // If the number of paths have been printed
                            // Reach the restriction stop the recursive call
                            // And update status to 2
                            if(*acc == limit){
                                status = 2;
                                return status;
                            }
                            // Otherwise, update acc by 1
                            // Print out the sub-dir's name
                            else{
                                *acc = *acc + 1;
                                printf("%s\n", dire_name);
                            }
                        }
                        // If the limit is reached stop doing the recursive call
                        // Update the status to 2 return it
                        if(status == 2){
                            status = 2;
                            return status;
                        }
                        // Otherwise
                        else{
                            // Keep track the exit status by doing the recursive call
                            if(status == 0){
                                status = find_dire_s(dire_name, limit, acc);
                            }
                            // If there are any error raised during the recursive call
                            // Set status to 1 and doing the recursive call
                            // without updating status
                            else{
                                status = 1;
                                find_dire_s(dire_name, limit, acc);
                            }
                        }
                    }
                    // If there is no restriction on the number of paths
                    // Do the recursive call until the bottom of the dir
                    else{
                        if(statbuf2.st_mtime < statbuf2.st_ctime){
                            printf("%s\n", dire_name);
                        }
                        if(status == 0){
                            status = find_dire_s(dire_name, limit, acc);
                        }
                        else{
                            status = 1;
                            find_dire_s(dire_name, limit, acc);
                        }
                    }
                }
            }
            closedir(dp);
        }
    }
    return status;
}

// This is function used for option n
/*
Inputs: file_path is a pointer of char indicates the name of path
limit indicates the limit of the number of directory can be printed out
if limiit is -1 then this indicates there is no restriction on the number
of directory
acc is a pointer to int used to track how many paths have been printed
Output: This function return the exit status
*/
int find_dire_n(char *file_path, int limit, int *acc){
    //Defined proper variables
    int status = 0;
    struct stat statbuf;
    // If the given file cannot be opened
    // Write the error message to stderr and update the status
    if(lstat(file_path, &statbuf)){
        fprintf(stderr, "%s: No such file or directory\n", file_path);
        status = 1;
    }
    // If the given path is a directory
    // Start to process the directory
    if(S_ISDIR(statbuf.st_mode)){
        DIR *dp;
        struct dirent *p;
        // If the directory cannot be opened write to the stderr
        // update the status
        if((dp = opendir(file_path)) == NULL){
            fprintf(stderr, "%s: Permission denied\n", file_path);
            status = 1;
        }
        // Otherwise, do the recursive call on every sub-directory
        else{
            while((p = readdir(dp))){
                // The algorithm should escape . and .. since
                // Doing recursive call on . and .. will raise stack overflow
                if(strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0){
                    // Create an array to hold the sub-dire's name
                    // Calculate the length of the sub-directory
                    char *dire_name;
                    int new_dir_len = (strlen(file_path) + 1 + strlen(p->d_name) + 1);
                    // Allocate space for the array of sub-dire
                    dire_name = malloc(sizeof(char) * new_dir_len);
                    // Call the function to fill the array with sub-dir's name
                    fill_path(file_path, p->d_name, dire_name, new_dir_len);
                    struct stat statbuf2;
                    // Try to access the info of sub-dire by using lstat
                    // If there is an error raised write it to stderr
                    if(lstat(dire_name, &statbuf2)){
                        fprintf(stderr, "%s: No such file or directory\n", dire_name);
                        status = 1;
                    }
                    // Check the m_time and c_time for the sub-dire
                    if(statbuf2.st_mtime != statbuf2.st_ctime){
                        // If the number of paths have been printed
                        // Reach the restriction stop the recursive call
                        // And update status to 2
                        if(*acc == limit){
                            status = 2;
                            return status;
                        }
                        // Otherwise, update acc by 1
                        // Print out the sub-dir's name
                        else{
                            *acc = *acc + 1;
                            printf("%s\n", dire_name);
                        }
                    }
                    // If the limit is reached stop doing the recursive call
                    // Update the status to 2 return it
                    if(status == 2){
                        return 2;
                    }
                    // Otherwise
                    else{
                        // Keep track the exit status by doing the recursive call
                        if(status == 0){
                            status = find_dire_n(dire_name, limit, acc);
                        }
                        // If there are any error raised during the recursive call
                        // Set status to 1 and doing the recursive call
                        // without updating status
                        else{
                            status = 1;
                            find_dire_n(dire_name, limit, acc);
                        }
                    }
                }
            }
            closedir(dp);
        }
    }
    return status;
}

// This function is used to fill an array with a given directory's name
/*
Inputs: file_path is a pointer of an array indicates the start directory
file_name is a pointer of an array indicates the sub dire's name
res is a pointer of an array to be filled
size is the number of chars can be filled into res array
Output: This function does not provide any output
Instead it will fill the res with the full name of the sub-directory
*/
void fill_path(char *file_path, char*file_name, char *res, int size){
    // First fill the array of start directory's name
    for(int i = 0; i < strlen(file_path); i++){
        res[i] = file_path[i];
    }
    // Adding an / to the array
    res[strlen(file_path)] = '/';
    // Then fill the rest of the array with subdirectory's name
    for(int j = 0; j < strlen(file_name); j++){
        res[strlen(file_path) + 1 + j] = file_name[j];
    }
    // Fill the terminating zero
    res[size - 1] = '\0';
}
