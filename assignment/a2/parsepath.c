#include <stdio.h>
#include <stdlib.h>
// There are two functions will be used for this program
// Function prototypes are defined here
void putdot(char *pathname);
void putpath(char *path_name, char *path, int length, int beg);
int parsepath(char *path, char **result, int size){
	// This is the pointer used to track the current character
	char *head = path;
	// count is used to determine how many paths have been parsed
	int count = 0;
	// This is used to determine the start-index of an parsed path
	int beg = 0;
	// This is used to determine the length of entire path
	int length = 0;
	// As long as the algorithm has not meet the terminating zero, the algorithm
	// will not stop
	while(*head != '\0'){
	    // If the current character is : then the algorithm will put the path
	    // Before the current character to a intermediate array
		if(*head == ':'){
		    // This calculates the distance of current character with
		    // the start index of the current path
			int distance = (head - (path + beg)) / sizeof(char);
			// Malloc space for path name
			char *path_name = NULL;
			// If this is an empty string
			// Just malloc two spaces
			// Call putdot to finish add dot to the intermediate array
			if(distance == 0){
			    path_name = malloc(sizeof(char) * 2);
			    putdot(path_name);
			}
			// If the current path is not an empty str
			// Malloc correct spaces based on the distance
			// Call putpath function to add path to the intermediate array
			else{
				path_name = malloc(sizeof(char) * (distance + 1));
				putpath(path_name, path, distance, beg);
			}
			// Update the beginning index
			beg = ((head - path) / sizeof(char));
			beg ++;
			// If the capacity of the result has not been exceeded
			// Add the pointer of intermediate array to the result
			if(count < size){
				result[count++] = path_name;
			}
			// Otherwise, this should return -1
			else{
				return -1;
			}
		}
		// Update the head pointer to the next character
		head ++;
		// Update the length of the entire path by 1
		length = length + 1;
	}
	// If there is no : in the middle of the path
	// Put entire path into the intermediate array by calling putpath
	// Then add pointer of the intermediate array to the result
	if(count == 0){
	    char *path_name = malloc(sizeof(char) * (length + 1));
	    putpath(path_name, path, length, beg);
	    path_name[length] = '\0';
	    if(count < size){
	        result[count++] = path_name;
	    }
	    else{
		return -1;
	    }
	}
	// Check the last character of the path
	else{
	    // If the distance > 0 add the last path to the intermediate array
	    char last_char = *(head - 1);
	    int distance = (head - (path + beg)) /sizeof(char);
	    if(distance > 0){
	        char *path_name = malloc(sizeof(char) * (distance + 1));
	        putpath(path_name, path, distance, beg);
	        if(count < size){
	            result[count++] = path_name;
	        }
	        else{
	            return -1;
	        }
	    // If the last character is ':'
	    // i.e) there is an empty str in the end of the path)
	    // Add dot to the intermediate array
	    }
	    else if(last_char == ':'){
	        char * path_name = malloc(sizeof(char) * 2);
	        putdot(path_name);
	        if(count < size){
	            result[count++] = path_name;
	        }
	        else{
	            return -1;
	        }
	    }
	}
	return count;
}
// This function is used to place . and terminating zero
/*
 Input:path_name is a pointer of an array of char to be placed
 Output: There is no return for this function
 Instead this function will place dot and terminating zero to the array 
 which path_name is pointing
 */
void putdot(char *path_name){
    path_name[0] = '.';
    path_name[1] = '\0';
}

// This function is used to place the directory name into an array
/*
 Input:path_name is a pointer of an array used to hold the parsed path
 path is a pointer of an array which is the name of parsed path
 length is an int indicates the length of the parsed path
 beg is an int indicates the start index of the parsed path
 Output: There is no return for this function
 Instead this function will place the name of parsed path to the array
 */
void putpath(char *path_name, char *path, int length, int beg){
    for(int i = 0; i < length; i++){
	    char temp = *(path + beg + i);
		path_name[i] = temp;
	}
	path_name[length] = '\0';
}
