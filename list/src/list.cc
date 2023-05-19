#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

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

	if (list == NULL) 
	{
		perror("list null pointer after calloc in list_create");
		exit(errno);
	}

	return list;
}

void list_free(list_t *list)
{
	assert(list && "null pointer in list_free");

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
	assert(list && "null pointer in list_size");

	return list->size;
}

int list_empty(list_t *list)
{
	assert(list && "null pointer in list_empty");
	
	return list->size == 0;
}

void list_erase(list_t *list, list_node_t *node)
{
	assert(list && "list null pointer in list_erase");
	assert(node && "node null pointer in list_empty");
	
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
	assert(list && "null pointer in list_back");
	
	return list->back;
}

list_node_t *list_front(list_t *list)
{
	assert(list && "null pointer in list_front");

	return list->front;
}

void list_pop_front(list_t *list)
{
	assert(list && "null pointer in list_pop_front");

	list_node_t *next = list->front->next;
	free(list->front);

	list->front = next;

	if (list->front)
		list->front->prev = NULL;
	else
		list->back = NULL;

	list->size--;
}

void list_pop_back(list_t *list)
{
	assert(list && "null pointer in list_pop_back");

	list_node_t *prev = list->back->prev;
	free(list->back);
	
	list->back = prev;
	
	if (list->back)
		list->back->next = NULL;
	else
		list->front = NULL;

	list->size--;
}

void list_push_front(list_t *list, keyT key, valueT value, int time)
{
	assert(list && "null pointer in list_push_front");
	
	list_node_t *node = (list_node_t*) calloc(1, sizeof(list_node_t));
	
	if (list == NULL) 
	{
		perror("list_node null pointer after calloc in list_push_front");
		exit(errno);
	}

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
	assert(list && "list null pointer in list_move_upfront");
	assert(node && "list_node null pointer in list_move_upfront");
	
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
	assert(node && "list_node null pointer in node_key");

	return node->key;
}

valueT node_value(list_node_t *node)
{
	assert(node && "list_node null pointer in node_value");

	return node->value;
}

int node_time(list_node_t *node)
{
	assert(node && "list_node null pointer in node_time");
	
	return node->time;
}

void list_dump(list_t *list)
{
	assert(list && "list null pointer in list_dump");

	int i = 0;
	list_node_t *cur = list->front;

	while (cur)
	{
		printf("<%d, %d, %d> ", cur->key, cur->value, cur->time);
		cur = cur->next;
		i++;
	}
	printf("\n");
}


list_node_t *node_next(list_node_t *node)
{
	assert(node && "list_node null pointer in node_next");
	
	return node->next;
}

void node_set_time(list_node_t *node, int time)
{
	assert(node && "list_node null pointer in node_set_time");

	node->time = time;
}