#include "LRUcache.h"
#include "list.h"
#include "hash_table.h"

#include <stdlib.h>

struct lru_cache_t
{
	htab_t *htab;
	list_t *cache;
	int size;
};

lru_cache_t *lru_create(int size)
{
	lru_cache_t *lru = (lru_cache_t*)calloc(1, sizeof(lru_cache_t));
	lru->size = size;
	lru->htab = htab_create(0, NULL);
	lru->cache = list_create();
	return lru;
}

void lru_free(lru_cache_t *lru)
{
	htab_free(lru->htab);
	list_free(lru->cache);
	free(lru);
}

int lru_lookup_update(lru_cache_t *lru, keyT key)
{
	list_node_t *find, *back;
	keyT erase_key;

	find = htab_find(lru->htab, key);

	if (!find)										// key not present in cache
	{
		if (list_size(lru->cache) == lru->size)		//cache is full
		{
			back = list_back(lru->cache);
			erase_key = node_key(back);
			htab_erase(lru->htab, erase_key);
			list_pop_back(lru->cache);			
		}
		list_push_front(lru->cache, key, 0);
		htab_insert(lru->htab, key);
		return 0;									//cache miss
	}
	list_move_upfront(lru->cache, find);
	return 1;										//cache hit
}