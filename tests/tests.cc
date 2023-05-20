#include <gtest/gtest.h>

#include "cache.h"

int main() 
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(cache, create)
{
    cache_t *cache = cache_create(10);
    ASSERT_TRUE(cache);
    ASSERT_TRUE(cache_size(cache) == 0);
    cache_free(cache);
}

TEST(cache, lookup)
{
    int res = 0;
    cache_t *cache = cache_create(10);
    for (int i = 0; i < 10; i++)
    {
        res = cache_lookup_update(cache, i % 4, i % 4, i + 1);
        if (i >= 4)
        {
            ASSERT_TRUE(res);
            ASSERT_TRUE(cache_size(cache) == 6);
        }
        else
            ASSERT_FALSE(res);
    }
    cache_free(cache);
}