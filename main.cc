#include "cache.h"
#include "PSScache.h"
#include "LRUcache.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	cache_t *cache = NULL;
	pss_cache_t *pss = NULL;
	lru_cache_t *lru = NULL;

	int cache_size = 0;
	int n = 0, key = 0, size = 0, time = 0, i = 0;
	int lru_hits = 0, cache_hits = 0, pss_hits = 0;
	scanf("%d %d", &cache_size, &n);

	cache = cache_create(cache_size);
	pss = pss_cache_create(cache_size);
	lru = lru_create(cache_size);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &key);
		size = 1;
		time = i + 1;
		pss_hits += pss_cache_lookup_update(pss, key, size, time);
		cache_hits += cache_lookup_update(cache, key, size, time);
		lru_hits += lru_lookup_update(lru, key, size, time);
	}

	cache_free(cache);
	lru_free(lru);
	pss_cache_free(pss);

	printf("cache: %d\npss: %d\nlru: %d\n", cache_hits, pss_hits, lru_hits);
}