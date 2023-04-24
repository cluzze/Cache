//Definition of list which stores hash table data

#pragma once

struct list_node_t;
struct list_t;

typedef struct list_t list_t;
typedef struct list_node_t list_node_t;

typedef int keyT;
typedef int valueT;

list_t *list_create();

void list_free(list_t *list);

void list_push_back(list_t *list, keyT key, valueT value);

void list_push_front(list_t *list, keyT key, valueT value);

void list_pop_back(list_t *list);

void list_pop_front(list_t *list);

list_node_t *list_back(list_t *list);

list_node_t *list_front(list_t *list);

void list_move_upfront(list_t *list, list_node_t *node);

int list_size(list_t *list);

int list_empty(list_t *list);

keyT node_key(list_node_t *node);

valueT node_value(list_node_t *node);

void list_dump(list_t *list);