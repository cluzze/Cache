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
		printf("\n");
	}
	lru_free(lru);
}