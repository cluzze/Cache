#include <gtest/gtest.h>

#include "cache.h"

typedef struct
{
    int key, size, time;
} item;

typedef struct
{
    item* items;
    int size;
    int exp_res;
} test_t;


int main() 
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

void free_test(test_t* test)
{
    free(test->items);
    free(test);
}

test_t* gen_test_1(int test_size, int cache_size)
{
    int i = 0;
    
    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    for (i = 0; i < test_size; i++)
    {
        test->items[i].key = i;
        test->items[i].size = 1;
        test->items[i].time = 0; 
    }

    test->exp_res = 0;

    return test;
}

test_t* gen_test_2(int test_size, int cache_size)
{
    int i = 0;
    
    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    for (i = 0; i < test_size; i++)
    {
        test->items[i].key = i % (cache_size / 2) + 1;
        test->items[i].size = i % (cache_size / 2) + 1;
        test->items[i].time = 1; 
    }

    test->exp_res = (test_size - (cache_size / 2)) / (cache_size / 2) * 2;

    return test;
}

test_t* gen_test_3(int test_size, int cache_size)
{
    int i = 0;
    
    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    for (i = 0; i < test_size; i++)
    {
        test->items[i].key = i % (cache_size / 2) + 1;
        test->items[i].size = i % (cache_size / 2) + 1;
        test->items[i].time = i; 
    }

    test->exp_res = (test_size - (cache_size / 2)) / (cache_size / 2);

    return test;
}

test_t* gen_test_4(int test_size, int cache_size)
{
    int i = 0;
    
    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    for (i = 0; i < test_size; i++)
    {
        test->items[i].key = i % 2;
        test->items[i].size = i % 2;
        test->items[i].time = i; 
    }

    test->exp_res = (test_size - 2);

    return test;
}

test_t* handwriten_test_1()
{
    int test_size = 5;

    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    test->items[0] = {1, 4, 1};
    test->items[1] = {2, 3, 2};
    test->items[2] = {3, 2, 3};
    test->items[3] = {1, 4, 4};
    test->items[4] = {2, 3, 5};

    test->exp_res = 0;

    return test;
}

test_t* handwriten_test_2()
{
    int test_size = 5;

    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    test->items[0] = {1, 3, 1};
    test->items[1] = {2, 7, 2};
    test->items[2] = {3, 2, 3};
    test->items[3] = {1, 1, 4};
    test->items[4] = {2, 7, 5};

    test->exp_res = 1;

    return test;
}

test_t* handwriten_test_3()
{
    int test_size = 10;

    test_t* test = NULL;
    test = (test_t*)calloc(1, sizeof(test_t));
    
    test->size = test_size;
    test->items = (item*)calloc(test->size, sizeof(item));

    test->items[0] = {1, 3, 1};
    test->items[1] = {2, 5, 2};
    test->items[2] = {1, 3, 3};
    test->items[3] = {3, 2, 4};
    test->items[4] = {2, 5, 5};    
    test->items[5] = {2, 5, 6};
    test->items[6] = {1, 3, 7};
    test->items[7] = {1, 3, 8};
    test->items[8] = {3, 2, 9};
    test->items[9] = {2, 5, 10};

    test->exp_res = 3;

    return test;
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

TEST(cache, test1)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(10);
    test_t* test = gen_test_1(100, 10);
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test2)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(10);
    test_t* test = gen_test_2(100, 10);
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test3)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(10);
    test_t* test = gen_test_3(100, 10);
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test4)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(10);
    test_t* test = gen_test_4(100, 10);
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test5)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(7);
    test_t* test = handwriten_test_1();
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test6)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(10);
    test_t* test = handwriten_test_2();
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}

TEST(cache, test7)
{
    int res = 0, i = 0;
    cache_t *cache = cache_create(9);
    test_t* test = handwriten_test_3();
    for (i = 0; i < test->size; i++)
    {
        if (cache_lookup_update(cache, test->items[i].key, test->items[i].size, test->items[i].time))
            res++;
    }
    ASSERT_EQ(res, test->exp_res);
    cache_free(cache);
    free_test(test);
}