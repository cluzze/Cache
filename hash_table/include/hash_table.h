//Definition of hash table implemented using separate chaining

#pragma once

#include "list.h"

struct htab_t;

typedef struct htab_t htab_t;

typedef const char* keyT;

typedef int valueT;

htab_t *htab_create(int size, int (*hash)(keyT));

void htab_free(htab_t *htab);

list_node_t *htab_find(htab_t *htab, keyT key);

void htab_erase(htab_t *htab, keyT key);

void htab_insert(htab_t *htab, keyT key);

int htab_size(htab_t *htab);

int htab_load_factor(htab_t *htab);

void htab_rehash(htab_t *htab, int size, int (*hash)(keyT));

void htab_dump(htab_t *htab);