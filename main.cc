#include "cache.h"
#include "PSScache.h"
#include "LRUcache.h"

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	cache_t *cache = NULL;

	int cache_size = 0;
	int n = 0, key = 0, size = 0, time = 0, i = 0;
	int cache_hits = 0;
	scanf("%d %d", &cache_size, &n);

	cache = cache_create(cache_size);

	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &key) != 1)
		{
			perror("invalid input");
			exit(errno);
		}

		size = 1;
		time = i + 1;
		cache_hits += cache_lookup_update(cache, key, size, time);
	}

	cache_free(cache);

	printf("%d\n", cache_hits);
}