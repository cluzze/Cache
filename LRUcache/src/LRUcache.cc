#include "LRUcache.h"
#include "list.h"
#include "hash_table.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h> 

struct lru_cache_t
{
	htab_t *htab;
	int capacity;
	int size;
};

lru_cache_t *lru_create(int size)
{
	assert(size);

	lru_cache_t *lru = (lru_cache_t*)calloc(1, sizeof(lru_cache_t));
	
	if (!lru)
	{
		perror("allocation fail in lru_create");
		exit(errno);
	}

	lru->capacity = size;
	lru->size = 0;
	lru->htab = htab_create(lru->capacity);
	
	return lru;
}

void lru_free(lru_cache_t *lru)
{
	assert(lru);

	htab_free(lru->htab);
	free(lru);
}

int lru_size(lru_cache_t *lru)
{
	return lru->size;
}

list_node_t* lru_last(lru_cache_t *lru)
{
	assert(lru);

	list_t *cache;
	list_node_t *back;
	
	cache = htab_list(lru->htab);
	back = list_back(cache);
	return back;
}

void lru_delete_last(lru_cache_t *lru)
{
	assert(lru);

	list_node_t *back;
	keyT erase_key;
	
	back = lru_last(lru);

	assert(back);

	lru->size -= node_value(back);
	erase_key = node_key(back);
	htab_erase(lru->htab, erase_key);
}

void lru_move_el(lru_cache_t *lru, list_node_t *find, int time)
{
	assert(lru);
	assert(find);

	list_t *cache = NULL;
	cache = htab_list(lru->htab);

	node_set_time(find, time);
	list_move_upfront(cache, find);
}

void lru_add_el(lru_cache_t *lru, keyT key, valueT size, int time)
{
	htab_insert(lru->htab, key, size, time);
	lru->size += size;	
}

list_node_t *lru_is_present(lru_cache_t *lru, int key)
{
	list_node_t *find = NULL;

	find = htab_find_list_node(lru->htab, key);

	return find;
}

int lru_lookup_update(lru_cache_t *lru, keyT key, valueT size, int time)
{
	assert(lru);

	list_node_t *find = NULL;
	list_t *cache = NULL;

	cache = htab_list(lru->htab);

	find = lru_is_present(lru, key);

	htab_dump(lru->htab);
	printf("\n");

	if (size > lru->capacity)
		return 0;

	if (find)
	{
		printf("found %d, %p\n", key, find);
		lru_move_el(lru, find, time);
		return 1;
	}
	//printf("cap: %d, csize: %d, size: %d\n", lru->capacity, lru->size, size);

	while (lru->capacity - lru->size < size)
	{
		lru_delete_last(lru);
	}

	lru_add_el(lru, key, size, time);

	return 0;
}

void lru_dump(lru_cache_t *lru)
{
	assert(lru);

	list_dump(htab_list(lru->htab));
}