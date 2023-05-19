#include "cache.h"
#include "LRUcache.h"
#include <stdio.h>

int main()
{
	cache_t *cache = NULL;
	lru_cache_t *lru = NULL;

	int cache_size = 0;
	int n = 0, key = 0, size = 0, time = 0, i = 0;
	int cache_hits = 0;
	scanf("%d %d", &cache_size, &n);

	cache = cache_create(cache_size);
	lru = lru_create(cache_size);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &key);
		size = 1;
		time = i;
		//cache_hits += cache_lookup_update(cache, key, size, time);
		cache_hits += lru_lookup_update(lru, key, 2, time);
		printf("%d\n", cache_hits);
		lru_dump(lru);
	}

	printf("%d\n", cache_hits);
}