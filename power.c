#include<stdio.h>
#include<stdlib.h>
int pow(int base, int power, int *count);
int pow(int base, int power, int *count){
    printf("Count is %d\n", *count);
    if(power == 0){
        return 1;
    }
    else if(power == 1){
        return base;
    }
    else if(power % 2 == 0){
        *count = *count+1;
        int a;
        a = pow(base, power / 2, count);
	printf("a is %d\n", a);
        return a * a;
    }
    else{
        *count = *count+1;
        return base * pow(base, power -1, count);
    }
}

int main(){
    int count = 0;
    int temp = 0;
    temp = pow(2, 46, &count);
    printf("The result is %d and there are %d calls\n", temp, count);
}
