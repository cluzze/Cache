#include <gtest/gtest.h>

#include "LRUcache.h"
#include "PSScache.h"

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

TEST(PSScache, lookup)
{
	pss_cache_t *cache = pss_cache_create(5);

	pss_cache_lookup_update(cache, 1, 1, 0);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 2, 1, 1);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 3, 2, 2);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 4, 2, 3);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 1, 4, 0);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 2, 1, 1);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 3, 3, 2);
	pss_cache_dump(cache);
	pss_cache_lookup_update(cache, 4, 5, 3);
	pss_cache_dump(cache);
	//ASSERT_TRUE(cache_space(cache) == 3);


	pss_cache_free(cache);
}