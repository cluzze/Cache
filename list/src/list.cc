#include "list.h"

#include <stdlib.h>
#include <stdio.h>

struct list_node_t {
	keyT key;
	valueT value;
	int time;
	list_node_t *next;
	list_node_t *prev;
};

struct list_t {
	list_node_t *front;
	list_node_t *back;
	int size;
};

list_t *list_create()
{
	list_t *list = (list_t*)calloc(1, sizeof(list_t));
	return list;
}

void list_free(list_t *list)
{
	list_node_t *node = NULL;

	while (list->front != NULL)
	{
		node = list->front->next;
		free(list->front);
		list->front = node;
	}

	free(list);

	return;
}

int list_size(list_t *list)
{
	return list->size;
}

int list_empty(list_t *list)
{
	return list->size == 0;
}

void list_erase(list_t *list, list_node_t *node)
{
	if (node == list->front)
	{
		list_pop_front(list);
	}
	else if (node == list->back)
	{
		list_pop_back(list);
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		list->size--;
		free(node);
	}
}

list_node_t *list_back(list_t *list)
{
	return list->back;
}

list_node_t *list_front(list_t *list)
{
	return list->front;
}

void list_pop_front(list_t *list)
{
	list_node_t *next = list->front->next;
	free(list->front);
	list->front = next;
	list->front->prev = NULL;
	list->size--;
}

void list_pop_back(list_t *list)
{
	list_node_t *prev = list->back->prev;
	free(list->back);
	list->back = prev;
	list->back->next = NULL;
	list->size--;
}

<<<<<<< HEAD
void list_push_front(list_t *list, keyT key, valueT value)
=======
void list_push_front(list_t *list, keyT key, valueT value, int time)
>>>>>>> marakulin
{
	list_node_t *node = (list_node_t*)calloc(1, sizeof(list_node_t));
	node->key = key;
	node->value = value;
<<<<<<< HEAD
=======
	node->time = time;
>>>>>>> marakulin

	if (list->size == 0)
	{
		list->front = node;
		list->back = node;
	}
<<<<<<< HEAD
	else if (list->size == 1)
	{
		node->next = list->back;
		node->prev = NULL;
		list->front = node;
		list->back->prev = node;
	}
=======
>>>>>>> marakulin
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

keyT node_key(list_node_t *node)
{
	return node->key;
}

<<<<<<< HEAD
=======
valueT node_value(list_node_t *node)
{
	node->value;
}

int node_time(list_node_t *node)
{
	return node->time;
}

>>>>>>> marakulin
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


list_node_t *list_next(list_t *list, list_node_t *node)
{
	return node->next;
}