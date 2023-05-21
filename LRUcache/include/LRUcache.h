#pragma once

//lru cache interface

#include "list.h"

struct lru_cache_t;

typedef int keyT;
typedef struct lru_cache_t lru_cache_t;

lru_cache_t* lru_create(int size);

void lru_free(lru_cache_t *lru);

int lru_size(lru_cache_t *lru);

list_node_t* lru_last(lru_cache_t *lru);

list_node_t* lru_is_present(lru_cache_t *lru, keyT key);

void lru_add_el(lru_cache_t *lru, keyT key, valueT value, int time);

void lru_move_el(lru_cache_t *lru, list_node_t *find, int time);

void lru_delete_last(lru_cache_t *lru);

int lru_lookup_update(lru_cache_t *lru, keyT key, valueT value, int time);

void lru_dump(lru_cache_t *lru);