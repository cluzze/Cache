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
	list_free(list);
}

TEST(list, )