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

int lru_lookup_update(lru_cache_t *lru, keyT key)
{
	list_node_t *find, *back;
	list_t *cache;
	keyT erase_key;

	cache = htab_list(lru->htab);
	find = htab_find(lru->htab, key);

/*	list_dump(cache);
	htab_dump(lru->htab);*/

	if (!find)										// key not present in cache
	{
		if (list_size(cache) == lru->size)			//cache is full
		{
			back = list_back(cache);
			erase_key = node_key(back);
			htab_erase(lru->htab, erase_key);
		}
		htab_insert(lru->htab, key, 1);
		return 0;									//cache miss
	}
	list_move_upfront(cache, find);
	return 1;										//cache hit
}