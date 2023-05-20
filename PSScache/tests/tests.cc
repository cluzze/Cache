#include <gtest/gtest.h>

#include "LRUcache.h"
#include "PSScache.h"

int main() 
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
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