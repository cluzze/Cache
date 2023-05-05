#include "list.h"

struct list_node_t 
{
	keyT key;
	valueT value;
	int time;
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
	list_node_t *prev = list->back->prev;
	free(list->back);
	list->back = prev;
	list->back->next = NULL;
	list->size--;
}

void list_push_front(list_t *list, keyT key, valueT value, int time)
{
	list_node_t *node = (list_node_t*)calloc(1, sizeof(list_node_t));
	node->key = key;
	node->value = value;
	node->time = time;

	if (list->size == 0)
	{
		list->front = node;
		list->back = node;
	}
	else
	{
		node->next = list->front;
		node->prev = NULL;
		list->front->prev = node;
		list->front = node;
	}
	list->size++;
}

void list_move_upfront(list_t *list, list_node_t *node)
{
	if (node == list->front)
		return;

	if (node == list->back)
	{
		list->back = node->prev;
		node->prev->next = NULL;
		node->prev = NULL;
		node->next = list->front;
		list->front->prev = node;
		list->front = node;
		return;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->prev = NULL;
	node->next = list->front;
	list->front->prev = node;
	list->front = node;

}

void list_free(list_t *list) 
{

valueT node_value(list_node_t *node)
{
	node->value;
}

int node_time(list_node_t *node)
{
	return node->time;
}

void list_dump(list_t *list)
{
	int i = 0;
	list_node_t *cur = list->front;
	printf("list:\n");
	while (cur)
	{
		printf("%d: <%d, %d> ", i, cur->key, cur->value);
		cur = cur->next;
		i++;
	}
	printf("\n");
}