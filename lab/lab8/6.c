#include <stdio.h>
#include <stdlib.h>

struct item {
    int key;
    int data;
    struct item *next;
};

struct item *head = NULL;

int main()
{
    extern void insert(int key, int data), delete(int key), printall();
    extern int search(int key);
	//Test case 1 delete from null
	delete(20);
	printall();
	//Test case 2 delete head with a single node
	insert(20, 2);
	delete(20);
	printall();
	//Test case 3 delete head with nodes after
	insert(20, 2);
	insert(30, 3);
	delete(30);
	printall();
	//Test case 4 delete from middle of the list
	insert(40, 4);
	insert(50, 5);
	delete(40);
	printall();
	//Test case 5 delete the last node with no node after
	delete(50);
	printall();
	//Test case 6 print the last and only node in the list
	delete(30);
	printall();
    /*insert(38, 3);
    insert(20, 2);
    insert(5, 0);
    insert(22, 6);
    insert(46, 18);

    printf("With all five items:\n");
    printall();
	delete(5);
	printall();
    delete(22);
    printall();
    delete(46);
    printall();
    delete(46);
    printall();
	*/
/*

    printf("After delete(22):\n");
    delete(22);
    printall();
    printf("After delete(5):\n");
    delete(5);
    printall();
    printf("delete(30) shouldn't do anything:\n");
    delete(30);
    printall();

*/

    return(0);
}


void insert(int key, int data)
{
    struct item *new;
	struct item** pp;
    /* create the new item */
    if ((new = malloc(sizeof(struct item))) == NULL) {
        fprintf(stderr, "out of memory!\n");  /* unlikely */
        exit(1);
    }
    new->key = key;
    new->data = data;
	for (pp = &head; (*pp)&& (*pp)->key < key; pp = &(*pp)->next);
	new->next=*pp;
	*pp = new;
 
}


void delete(int key)
{
	struct item *p;
	p = head;
	if (p != NULL) {
		if (p->key == key) {
			struct item *nex = head->next;
			free(p);
			head = nex;
		}
		else {
			struct item* prev;
			prev = NULL;
			for (p = head; p && p->key != key; p = p->next) {
				prev = p;
			}
			if (p && p->key == key) {
				prev->next = p->next;
				free(p);
			}
		}
	}
}


int search(int key) /* returns -1 if not found */
{
    struct item *p;

    for (p = head; p && p->key < key; p = p->next)
        ;
    if (p && p->key == key)
        return(p->data);
    else
        return(-1);
}


void printall()
{
    struct item *p;
    for (p = head; p; p = p->next)
        printf("%d: %d\n", p->key, p->data);
    printf("[end]\n");
}
