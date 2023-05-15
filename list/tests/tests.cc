#include "list.h"

#include <gtest/gtest.h>

// testing list functions: create, push_front, erase


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
	ASSERT_TRUE(list_front(list) == NULL);
	ASSERT_TRUE(list_back(list) == NULL);
	list_free(list);
}

TEST(list, push_front)
{
	list_t *list = list_create();
	list_node_t *node = NULL;

	list_push_front(list, 1, 1, 1);
	ASSERT_TRUE(list_size(list) == 1);
	ASSERT_TRUE(list_front(list) == list_back(list));
	ASSERT_TRUE(list_front(list) != NULL);

	for (int i = 0; i < 10; i++)
	{
		list_push_front(list, i, i, i);
		node = list_front(list);
		ASSERT_TRUE(list_size(list) == i + 2);
		ASSERT_TRUE(node_key(node) == i);
	}

	list_free(list);
}

TEST(list, erase)
{
	list_t *list = list_create();
	list_node_t *node = NULL;

	list_push_front(list, 1, 1, 1);
	ASSERT_TRUE(list_size(list) == 1);
	ASSERT_TRUE(list_front(list) == list_back(list));
	ASSERT_TRUE(list_front(list) != NULL);

	list_push_front(list, 2, 2, 2);
	ASSERT_TRUE(list_size(list) == 2);
	ASSERT_TRUE(list_front(list) != list_back(list));
	ASSERT_TRUE(list_front(list) != NULL);

	list_erase(list, list_back(list));
	ASSERT_TRUE(list_size(list) == 1);
	ASSERT_TRUE(list_back(list) != NULL);
	ASSERT_TRUE(list_back(list) == list_front(list));
	
	list_erase(list, list_back(list));
	ASSERT_TRUE(list_back(list) == NULL);
	ASSERT_TRUE(list_front(list) == NULL);
	ASSERT_TRUE(list_size(list) == 0);

	for (int i = 0; i < 10; i++)
	{
		list_push_front(list, i, i, i);
	}

	node = list_front(list);
}