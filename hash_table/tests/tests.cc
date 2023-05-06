#include <gtest/gtest.h>

#include "hash_table.h"
#include "stdlib.h"

int main() 
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

TEST(htab, create)
{
	htab_t *htab = htab_create(10);
	ASSERT_TRUE(htab);
	ASSERT_EQ(htab_size(htab), 10);
	ASSERT_EQ(htab_load_factor(htab), 0);
	htab_free(htab);
}

TEST(htab, insert)
{
	int size = 20;
	htab_t *htab = htab_create(size);
// checking that nodes are adding correctly
	for (int i = 0; i < 10; i++) {
		htab_insert(htab, i, 0);
		ASSERT_EQ(htab_load_factor(htab), i + 1);
		ASSERT_EQ(htab_size(htab), size);
		ASSERT_TRUE(htab_find_hash_node(htab, i));
		ASSERT_EQ(list_size(htab_list(htab)), i + 1);
		ASSERT_EQ(node_key(list_front(htab_list(htab))), i);
	}
// checking that nodes dont add again
	for (int i = 0; i < 10; i++) {
		htab_insert(htab, i, 0);
		ASSERT_EQ(htab_load_factor(htab), 10);
		ASSERT_EQ(htab_size(htab), size);
		ASSERT_TRUE(htab_find_hash_node(htab, i));
		ASSERT_EQ(list_size(htab_list(htab)), 10);
	}
	
	htab_free(htab);
	htab = htab_create(size);

// checking with rand numbers
	for (int i = 0; i < 20; i++)
	{
		int num = rand() % 100;
		int load_factor = htab_load_factor(htab);

		if (htab_find_hash_node(htab, num)) 
		{
			htab_insert(htab, num, 0);
			ASSERT_EQ(htab_load_factor(htab), load_factor);
			ASSERT_EQ(htab_size(htab), size);	
		}
		else
		{
			htab_insert(htab, num, 0);
			ASSERT_TRUE(htab_find_hash_node(htab, num));
			ASSERT_EQ(htab_size(htab), size);
			ASSERT_EQ(htab_load_factor(htab), load_factor + 1);
			ASSERT_EQ(node_key(list_front(htab_list(htab))), num);
		}
	}

	htab_free(htab);
}

TEST(htab, rehash)
{
	int size = 5;
	htab_t *htab = htab_create(size);
	int load_factor = htab_load_factor(htab);

// checking that rehash work correctly 
	for (int i = 0; i < 100; i++) {
		load_factor = htab_load_factor(htab);
		if (i == size - 1)
		{
			size += 10;
			htab_rehash(htab, size);
			ASSERT_EQ(htab_load_factor(htab), load_factor);
			ASSERT_EQ(htab_size(htab), size);
		}
				
		htab_insert(htab, i, 0);
		ASSERT_TRUE(htab_find_hash_node(htab, i));
		ASSERT_EQ(node_key(list_front(htab_list(htab))), i);
	}


	htab_free(htab);
}

TEST(htab, erase)
{
	int size = 10;
	htab_t *htab = htab_create(size);
	int load_factor = htab_load_factor(htab);

// add nodes
	for (int i = 0; i < size; i++) {
		htab_insert(htab, i, 0);
	}
// checking

	for (int i = 0; i < size; i++) {
		load_factor = htab_load_factor(htab);
		htab_erase(htab, i);
		htab_dump(htab);
		ASSERT_EQ(htab_load_factor(htab), load_factor - 1);
		ASSERT_EQ(htab_size(htab), size);
		ASSERT_FALSE(htab_find_hash_node(htab, i));
		ASSERT_EQ(list_size(htab_list(htab)), load_factor - 1);
	}
}