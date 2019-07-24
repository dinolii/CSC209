#include <stdio.h>

struct item {
    int key;
    int data;
    struct item *next;
};

struct item *head = NULL;

int main()
{
    extern void filllist(), printall();
    filllist();
    printall();
    return(0);
}


void filllist()
{
    static struct item a, b, c, d;
    head = &a;
    a.key = 5;
    a.data = 0;
    a.next = &b;
    b.key = 20;
    b.data = 2;
    b.next = &c;
    c.next = &d;
    c.key = 22;
    c.data = 6;
    d.key = 38;
    d.data = 3;
    d.next = NULL;
}


void printall()
{
    struct item *p;
    for (p = head; p; p = p->next)
        printf("%d: %d\n", p->key, p->data);
    printf("[end]\n");
}
