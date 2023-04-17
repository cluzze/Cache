#include "list.h"

struct list_node_t 
{
	keyT key;
	valueT value;
	list_node_t *next;
	list_node_t *prev;
};

struct list_t
{
	list_node_t *front;
	list_node_t *back;
	int size;
};

list_t *list_create() 
{

}

void list_free(list_t *list) 
{

}