#include <stdio.h>
#include <math.h>
int main(){
    int c;
    while ((c=getchar())!= EOF){
	int guess = c;
        double sqt = sqrt(guess);
        double half = guess * 0.5;
        printf("%f\n", sqt);
        printf("%f\n", half);
}
    return 0;
}
