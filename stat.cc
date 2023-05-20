#include "cache.h"
#include "PSScache.h"
#include "LRUcache.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <random>

int main()
{
	cache_t *cache = NULL;
	pss_cache_t *pss = NULL;
	lru_cache_t *lru = NULL;
	
	std::random_device dev;
	std::mt19937 rng(dev());
	
	int cache_size = 0;
	int n = 0, key = 0, size = 0, time = 0, i = 0;
	int lru_hits = 0, cache_hits = 0, pss_hits = 0;
	
	for (i = 10; i < 960; i+= 50)
	{
		cache_size = i;

		cache = cache_create(cache_size);
		pss = pss_cache_create(cache_size);
		lru = lru_create(cache_size);

		std::vector<std::pair<int, int>> keys(i);
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, cache_size / 4);

		for (int j = 0; j < i; j++)
		{
			keys[j].first = j;
			keys[j].second = dist(rng);
		}

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(keys.begin(), keys.end(), std::default_random_engine(seed));

		for (int j = 0; j < i; j++)
		{
			pss_hits += pss_cache_lookup_update(pss, keys[j].first, keys[j].second, time);
			cache_hits += cache_lookup_update(cache, keys[j].first, keys[j].second, time);
			lru_hits += lru_lookup_update(lru, keys[j].first, keys[j].second, time);
		}

		cache_free(cache);
		lru_free(lru);
		pss_cache_free(pss);

		printf("cache: %d\npss: %d\nlru: %d\n", cache_hits, pss_hits, lru_hits);
	}
}