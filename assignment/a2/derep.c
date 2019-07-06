#include <stdio.h>
#include <string.h>
// There are three functions will be used for this program
// Function prototypes are defined here
void process(FILE*fp);
void putint(int number);
void putchars(char *chars, int size);
int main(int argc, char**argv){
    // Declare necessary variables and the function used to process file
    int i;
    FILE*fp;
    extern void process(FILE* fp);
    int status = 0;
    // If there is no command line argument process the sdin
    if(argc == 1){
        process(stdin);
    }
    // Otherwise loop every argument
    else{
        for(i=1; i<argc; i++){
            // If the argument is - then process stdin too
            if(strcmp(argv[i], "-") == 0){
                process(stdin);
            }
            // Otherwise try to open the file
            // In case the file there is an error, write it to stderr
            else{
   		        fp = fopen(argv[i], "r");
		        if(fp  == NULL){
		            perror(argv[i]);
		            status = 1;
		        }
                // Process file and close it after exectuion
			else{
		            process(fp);
  		            fclose(fp);
			}
	        }
        }
    }
    return status;
}
// This function is used to process every line of the file
/*
 Input:fp is a pointer of a file to be processed
 Output: There is no return for this function
 Instead this function will write the result to stdout directly
 */
void process(FILE* fp){
    // Declare functions and varibales for this function
    extern void putchars(char *chars, int size);
    extern void putint(int number);
    int previous = 0;
    int c;
    int count = 1;
    // These two char arrays contain characters that will be wrote to stdout
    char temp[] = {' ', 'm', 'o', 'r', 'e', ' '};
    char temp2[] = {' ', 'b', 'y', 't', 'e', 's', ']'};
    // Process every character until the last one
    while((c = getc(fp)) != EOF){
        // If this is the first character in the file, assign itself to previous
	    if(previous == 0){
	        previous = c;
            putchar(c);
	    }
        // When the current character is not same as the prvious character
        // Check whether the previous character appears more than 10 time
        // If so, call the functions to write info to stdout
        // Otherwise reassign variables
	    else if(previous != c){
	        if (count > 10){
		        int times = count - 10;
                putint(times);
                putchars(temp, sizeof(temp) / sizeof(char));
                putint(previous);
                putchars(temp2, sizeof(temp2) / sizeof(char));
	        }
	        previous = c;
	        putchar(c);
	        count = 1;
	    }
        // When the current character is same with previous character
        // When the count is less or equal to 9(Before the current character)
        // Put the character into stdout
        // After that if there are 9 appearances before, then write [ to stdout
        // Update count
        else if(previous == c){
	        if(count <= 9){
	            putchar(c);
	        }
            if(count == 10){
	            putchar('[');
	        }
	        count = count + 1;
	    }
   }
   // In case there is a character appears more than 10 times after executing loop
   // Apply the same strategy as above
    if(count > 10){
    	int times = count - 10;
        putint(times);
        putchars(temp, sizeof(temp) / sizeof(char));
        putint(previous);
        putchars(temp2, sizeof(temp2) / sizeof(char));
    }
}
/*
 Inputs: chars is an array of charactes, size is the length of the char array
 Output: This function has no output, instead it writes info to stdout
 Descrption: This function loops over every character in the array
 and write the character to stdout
 */
void putchars(char *chars, int size){
    int i;
    for(i=0; i<size; i++){
        putchar(chars[i]);
    }
}
/*
 Input: number is an int
 Output: This function has no return value, it writes every digit of
 the number to stdout
 Decription: When this number has more than 1 digit, it will do a recursive
 call with multipling a factor of 1 / 10.  Then, after reaching the base case
 it writes every digit to the stdout.
 */
void putint(int number){
    if(number / 10){
        putint(number / 10);
    }
    putchar(number % 10 + '0');
}

