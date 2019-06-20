/*
 * demonstrate how to do some stuff with unix times
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    extern void doit(long t);
    if (argc == 1) {
	doit(1234567890L);
    } else {
	int i;
	for (i = 1; i < argc; i++)
	    doit(atol(argv[i]));
    }
    return(0);
}


static char *monthname[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"
};

void doit(long t_arg)
{
    time_t t = t_arg;  /* time_t may or may not be the same as long */
    struct tm *r = localtime(&t);
    printf("Your time_t numeric value is %ld\n", t_arg);
    printf("ctime says: %s", ctime(&t));
    printf("The year is %d\n", 1900 + r->tm_year);
    printf("The month is %d\n", r->tm_mon + 1);
    printf("The time is %02d:%02d\n", r->tm_hour, r->tm_min);
    printf("I like to spell that month '%s'\n", monthname[r->tm_mon]);
    t += 12 * 60 * 60;
    printf("Twelve hours later, it will be %s", ctime(&t));
}
