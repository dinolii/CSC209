#include <stdio.h>
#include <ctype.h>
int main(int argc,char**argv){
    if(argc != 2){
	fprintf(stderr, "usage: %s str\nYou should only give one str\n", argv[0]);
	return (1);
	}
    else{
    	char*temp;
    	temp=argv[1];
        char*end;
	while(*temp!='\0'){
            end=temp;
            temp++;
            }
        char*beg;
        beg=argv[1];
	
        while(beg < end){
        char beg_char = *beg;
        char end_char = *end;
            while(!isalnum(beg_char)){
               beg++;
                beg_char = *beg;
            }
           while(!isalnum(end_char)){
		end --;
		end_char = *end;
            }
        beg_char = tolower(beg_char);
        end_char = tolower(end_char);
       if(beg_char != end_char){
	return(1);
        } 
	else{
	beg++;
	end--;
}
        }
    return (0);
}
}
