#include "list.h"

#include <gtest/gtest.h>

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

TEST(list, create)
{
	list_t *list = list_create();
	ASSERT_TRUE(list); 
	ASSERT_TRUE(list_size(list) == 0);
	list_free(list);
}

TEST(list, push_back)
{
	list_t *list = list_create();

	list_free(list);
}