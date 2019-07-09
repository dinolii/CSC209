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

    insert(1, 1);
    printall();
    insert(5, 2);
    printall();
    insert(2, 3);
    printall();
    insert(7, 4);
    printall();
    insert(6, 5);
    printf("With all five items:\n");
    printall();
    insert(6, 4);
    printall();

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
	struct item *p = head;
	struct item* item;
	item = malloc(sizeof(struct item));
	if (item == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	else {
		item->key = key;
		item->data = data;
		// Insert to the head
		if (head == NULL) {
			item->next = head;
			head = item;
		}
		else if(head != NULL && key < p->key){
			item->next = head;
			head =item;
		}
		else{
		int found = 0;
		// Insert to the middle
		while (p != NULL && p->next != NULL && found != 1) {
			if (p->key <= key && p->next->key >= key) {
				found = 1;
				item->next = p->next;
				p->next = item;
			}
 			p = p->next;
		}
		if (found == 0) {
			p->next = item;
		}
		}
	}
}


void delete(int key)
{
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
