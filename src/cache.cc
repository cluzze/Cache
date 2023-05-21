//slru cache interface implementation

#include "cache.h"
#include "hash_table.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h> 

struct cache_t
{
	int capacity;
	int size;
	int n;
	list_node_t **keys;
	htab_t *htab;
};

cache_t *cache_create(int size)
{
	assert(size > 0);

	cache_t *cache = NULL;
	cache = (cache_t*)calloc(1, sizeof(cache_t));

	if (!cache)
	{
		perror("allocation fail in cache_create");
		exit(errno);
	}

	cache->capacity = size;
	cache->size = 0;
	cache->n = 0;
	cache->keys = (list_node_t**)calloc(cache->capacity, sizeof(list_node_t*));

	if (!cache->keys)
	{
		perror("allocation fail in cache_create");
		exit(errno);
	}

	cache->htab = htab_create(cache->capacity);

	return cache;
}

void cache_free(cache_t *cache)
{
	assert(cache);

	htab_free(cache->htab);
	free(cache->keys);
	free(cache);
}

int get_value(list_node_t *node, int time)
{
	assert(node);
	return node_value(node) * (time - node_time(node));
}

void swap(list_node_t **a, list_node_t **b)
{
	list_node_t *tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(list_node_t **arr, int low, int high, int time)
{
	assert(arr);
	int pivot = 0;
	int i = low, j = 0;

	pivot = get_value(arr[low], time);

	for (j = low + 1; j <= high; ++j)
	{
		if (get_value(arr[j], time) < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[low], &arr[i]);
	return i;
}

void qsort_impl(list_node_t **arr, int low, int high, int time)
{
	int pi;

	if (low >= high)
		return;
	
	pi = partition(arr, low, high, time);
	
	if (pi > low)
		qsort_impl(arr, low, pi - 1, time);
	
	qsort_impl(arr, pi + 1, high, time);
}

void qqsort(list_node_t **arr, int len, int time)
{
	qsort_impl(arr, 0, len - 1, time);
}

void cache_add_el(cache_t *cache, int key, int size, int time)
{
	assert(cache);
	list_t *list = NULL;

	list = htab_list(cache->htab);
	htab_insert(cache->htab, key, size, time);
	cache->size += size;

	cache->keys[cache->n] = list_front(list);
	cache->n++;
}

void cache_del_el(cache_t *cache, list_node_t *node)
{
	int erase_key = 0;

	erase_key = node_key(node);
	cache->size -= node_value(node);
	htab_erase(cache->htab, erase_key);
	cache->n--;
}

int cache_lookup_update(cache_t *cache, int key, int size, int time)
{
	assert(cache);

	int free_space = 0;
	list_node_t *find = NULL;

	if (size > cache->capacity)
		return 0;

	find = htab_find_list_node(cache->htab, key);

	if (find)
	{
		node_set_time(find, time);
		return 1;
	}

	free_space = cache->capacity - cache->size;

	if (free_space >= size)
	{
		cache_add_el(cache, key, size, time);
		return 0;
	}

	qqsort(cache->keys, cache->n, time);

	while (cache->capacity - cache->size < size)
	{
		find = cache->keys[cache->n - 1];

		cache_del_el(cache, find);
	}

	cache_add_el(cache, key, size, time);
	return 0;
}

int cache_size(cache_t *cache)
{
	return cache->size;
}

void cache_dump(cache_t *cache)
{
	assert(cache);
	int i = 0;
	list_node_t *node = NULL;

	for (i = 0; i < cache->n; i++)
	{
		node = cache->keys[i];
		printf("<%d, %d, %d>\n", node_key(node),
								node_value(node),
								node_time(node));
	}
	printf("\n");
}

