#pragma once

//hash table interface

#include "list.h"

struct htab_t;

typedef struct htab_t htab_t;

typedef struct htab_node_t htab_node_t;

typedef int keyT;

typedef int valueT;

int default_hash(keyT key, int size);

htab_t *htab_create(int size);

void htab_free(htab_t *htab);

void free_node(htab_t *htab);

list_node_t *htab_find_list_node(htab_t *htab, keyT key);

htab_node_t *htab_find_hash_node(htab_t *htab, keyT key);

int htab_size(htab_t *htab);

int htab_load_factor(htab_t *htab);

list_t *htab_list(htab_t *htab);

void htab_dump(htab_t *htab);

void htab_erase(htab_t *htab, keyT key);

void htab_insert(htab_t *htab, keyT key, int value, int time);

void htab_insert_list_node(htab_t *htab, list_node_t *list_node);

void htab_rehash(htab_t *htab, int size);