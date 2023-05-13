#include "LRUcache.h"
#include "list.h"
#include "hash_table.h"

#include <stdlib.h>
#include <stdio.h>

struct lru_cache_t
{
	htab_t *htab;
	int size;
};

lru_cache_t *lru_create(int size)
{
	lru_cache_t *lru = (lru_cache_t*)calloc(1, sizeof(lru_cache_t));
	lru->size = size;
	lru->htab = htab_create(size);
	return lru;
}

void lru_free(lru_cache_t *lru)
{
	htab_free(lru->htab);
	free(lru);
}

list_node_t* lru_last(lru_cache_t *lru)
{
	list_t *cache;
	list_node_t *back;
	keyT erase_key;
	
	cache = htab_list(lru->htab);
	back = list_back(cache);
	return back;
}

void lru_delete_last(lru_cache_t *lru)
{
	list_node_t *back;
	keyT erase_key;
	
	back = lru_last(lru);	
	erase_key = node_key(back);
	htab_erase(lru->htab, erase_key);
}


list_node_t* lru_is_present(lru_cache_t *lru, keyT key)
{
	list_node_t *find;

	find = htab_find_list_node(lru->htab, key);

	return find;
}

void lru_add_el(lru_cache_t *lru, keyT key, valueT value, int time)
{
	list_t *cache = NULL;

	cache = htab_list(lru->htab);

	if (list_size(cache) == lru->size)			//cache is full
	{
		lru_delete_last(lru);
	}
	htab_insert(lru->htab, key, value, time);
}

void lru_move_el(lru_cache_t *lru, list_node_t *find, int time)
{
	list_t *cache = NULL;
	cache = htab_list(lru->htab);

	node_set_time(find, time);
	list_move_upfront(cache, find);
}

int lru_lookup_update(lru_cache_t *lru, keyT key, valueT value, int time)
{
	list_node_t *find;
	list_t *cache;

	cache = htab_list(lru->htab);

	find = lru_is_present(lru, key);

	if (!find)										// key not present in cache
	{
		lru_add_el(lru, key, value, time);
		return 0;									//cache miss
	}

	lru_move_el(lru, find, time);

	return 1;										//cache hit
}

void lru_dump(lru_cache_t *lru)
{
	list_dump(htab_list(lru->htab));
}