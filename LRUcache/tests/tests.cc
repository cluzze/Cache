
#include "LRUcache.h"
#include <gtest/gtest.h>

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
        lru_lookup_update(lru, i, i, i + 1);
        //printf("%d, %d\n", i % 4, lru_size(lru));
        //lru_dump(lru);
    }
    lru_free(lru);
}
