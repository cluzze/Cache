//pss cache interface implementation

#include "PSScache.h"
#include "LRUcache.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h> 

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
	assert(capacity);

	pss_cache_t *cache = NULL;
	int i = 0;

	cache = (pss_cache_t*)calloc(1, sizeof(pss_cache_t));
	if (!cache)
	{
		perror("allocation fail in pss_cache_create");
		exit(errno);
	}

	cache->capacity = capacity;
	cache->size = 0;
	cache->n = log2(capacity) + 1;
	cache->lru = (lru_cache_t**)calloc(cache->n, sizeof(lru_cache_t*));
	
	if (!cache->lru)
	{
		perror("allocation fail in pss_cache_create");
		exit(errno);
	}

	for (i = 0; i < cache->n; i++)
	{
		cache->lru[i] = lru_create(capacity);
	}

	return cache;
}

void pss_cache_free(pss_cache_t *cache)
{
	assert(cache);

	int i = 0;
	for (i = 0; i < cache->n; i++)
	{
		lru_free(cache->lru[i]);
	}
	free(cache->lru);
	free(cache);
}

int pss_cache_space(const pss_cache_t *cache)
{
	assert(cache);

	return cache->capacity - cache->size;
}

lru_cache_t* find_lru(pss_cache_t *cache, int time) // overflow S * T
{
	assert(cache);

	int i = 0;
	lru_cache_t *max = NULL, *cur;
	list_node_t *node = NULL;
	int max_value = 0;

	for (i = 0; i < cache->n; i++)
	{
		cur = cache->lru[i];
		node = lru_last(cur);
		if (!node)
			continue;

		if (max_value < node_value(node) * (time - node_time(node)))
		{
			max = cur;
			max_value = node_value(node) * (time - node_time(node));
		}
	}

	return max;
}

int pss_cache_lookup_update(pss_cache_t *cache, int key, int size, int time)
{
	assert(cache);

	if (size > cache->capacity)
		return 0;

	int freed_size = 0;
	int i = 0;
	list_node_t *node = NULL;
	list_node_t *find = NULL;
	lru_cache_t *max = NULL;

	if (size > cache->capacity)
		return 0;

	i = log2(size);

	assert(i < cache->n);

	find = lru_is_present(cache->lru[i], key);

	if (find)
	{
		lru_move_el(cache->lru[i], find, time);
		return 1;
	}

	while (size > cache->capacity - cache->size)
	{
		max = find_lru(cache, time);
		node = lru_last(max);
		freed_size = node_value(node);
		cache->size -= freed_size;
		lru_delete_last(max);
	}

	lru_add_el(cache->lru[i], key, size, time);
	cache->size += size;

	return 0;
}

void pss_cache_dump(const pss_cache_t *cache)
{
	int i = 0;
	printf("free space: %d\n", pss_cache_space(cache));
	for (i = 0; i < cache->n; i++)
	{
		printf("%d: ", i);
		lru_dump(cache->lru[i]);
	}
}