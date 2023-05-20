#include "PSScache.h"
#include "LRUcache.h"

#include <stdlib.h>
#include <stdio.h>

struct pss_cache_t {
	int capacity; // M
	int size;
	int n;
	lru_cache_t **lru;
};

int log2(int x)
{
	int i = 0, y = 1;
	while (y < x)
	{
		y *= 2;
		i++;
	}
	return i;
}

pss_cache_t *pss_cache_create(int capacity)
{
	pss_cache_t *cache = NULL;
	int i = 0;
	cache = (pss_cache_t*)calloc(1, sizeof(pss_cache_t));
	cache->capacity = capacity;
	cache->size = 0;
	cache->n = log2(capacity) + 1;
	cache->lru = (lru_cache_t**)calloc(cache->n, sizeof(lru_cache_t*));
	for (i = 0; i < cache->n; i++)
	{
		cache->lru[i] = lru_create(capacity);
	}
	return cache;
}

void pss_cache_free(pss_cache_t *cache)
{
	int i = 0;
	for (i = 0; i < cache->n; i++)
	{
		lru_free(cache->lru[i]);
	}
	free(cache->lru);
	free(cache);
}

int pss_cache_space(pss_cache_t *cache)
{
	return cache->capacity - cache->size;
}

lru_cache_t* find_lru(pss_cache_t *cache, int time) // overflow S * T
{
	int i = 0;
	lru_cache_t *min = NULL, *cur;
	list_node_t *node = NULL;
	int min_value = 1e9;

	for (i = 0; i < cache->n; i++)
	{
		cur = cache->lru[i];
		node = lru_last(cur);
		if (!node)
			continue;

		if (min_value > node_value(node) * (time - node_time(node)))
		{
			min = cur;
			min_value = node_value(node) * (time - node_time(node));
		}
	}

	return min;
}

int pss_cache_lookup_update(pss_cache_t *cache, int key, int size, int time)
{
	int freed_size = 0;
	int i = 0;
	list_node_t *node = NULL;
	list_node_t *find = NULL;
	lru_cache_t *min = NULL;

	if (size > cache->capacity)
		return 0;
	
	i = log2(size);

	find = lru_is_present(cache->lru[i], key);

	if (find)
	{
		lru_move_el(cache->lru[i], find, time);
		return 1;
	}

	while (size > cache->capacity - cache->size)
	{
		min = find_lru(cache, time);
		node = lru_last(min);
		freed_size = node_value(node);
		cache->size -= freed_size;
		lru_delete_last(min);
	}

	lru_add_el(cache->lru[i], key, size, time);
	cache->size += size;

	return 0;
}

void pss_cache_dump(pss_cache_t *cache)
{
	int i = 0;
	printf("free space: %d\n", pss_cache_space(cache));
	for (i = 0; i < cache->n; i++)
	{
		printf("%d: ", i);
		lru_dump(cache->lru[i]);
	}
}