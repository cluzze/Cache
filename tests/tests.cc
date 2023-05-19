#include <gtest/gtest.h>

#include "LRUcache.h"
#include "cache.h"

int main() 
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(lru, create)
{
	lru_cache_t *lru = lru_create(10);
	ASSERT_TRUE(lru != NULL);
	lru_free(lru);
}

TEST(lru, lookup)
{
	lru_cache_t *lru = lru_create(3);
	for (int i = 0; i < 10; i++)
	{
		lru_lookup_update(lru, i % 4, i % 4, i);
	}
	lru_free(lru);
}

TEST(cache, lookup)
{
	cache_t *cache = cache_create(5);

	cache_lookup_update(cache, 1, 1, 0);
	cache_dump(cache);
	cache_lookup_update(cache, 2, 1, 1);
	cache_dump(cache);
	cache_lookup_update(cache, 3, 2, 2);
	cache_dump(cache);
	cache_lookup_update(cache, 4, 2, 3);
	cache_dump(cache);
	cache_lookup_update(cache, 1, 4, 0);
	cache_dump(cache);
	cache_lookup_update(cache, 2, 1, 1);
	cache_dump(cache);
	cache_lookup_update(cache, 3, 3, 2);
	cache_dump(cache);
	cache_lookup_update(cache, 4, 5, 3);
	cache_dump(cache);
	//ASSERT_TRUE(cache_space(cache) == 3);


	cache_free(cache);
}