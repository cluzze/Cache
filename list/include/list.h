#pragma once

//List interface

struct list_node_t;
struct list_t;

typedef struct list_t list_t;
typedef struct list_node_t list_node_t;

typedef int keyT;
typedef int valueT;

list_t *list_create();

void list_free(list_t *list);

void list_push_back(list_t *list, keyT key, valueT value);

void list_push_front(list_t *list, keyT key, valueT value, int time);

void list_pop_back(list_t *list);

void list_pop_front(list_t *list);

list_node_t *list_back(const list_t *list);

list_node_t *list_front(const list_t *list);

void list_move_upfront(list_t *list, list_node_t *node);

int list_size(const list_t *list);

int list_empty(const list_t *list);

keyT node_key(const list_node_t *node);

void list_erase(list_t *list, list_node_t *node);

void list_dump(const list_t *list);

keyT node_key(const list_node_t *node);

valueT node_value(const list_node_t *node);

int node_time(const list_node_t *node);

void list_erase(list_t *list, list_node_t *node);

list_node_t *node_next(const list_node_t *node);

void node_set_time(list_node_t *node, int time);
