#include <gtest/gtest.h>

#include "hash_table.h"

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
	htab_t *htab = htab_create(10);

	for (int i = 0; i < 10; i++) {
		htab_insert(htab, i, 0);
		ASSERT_TRUE(htab_find_hash_node(htab, i));
		ASSERT_EQ(htab_size(htab), 10);
		ASSERT_EQ(htab_load_factor(htab), i);
		ASSERT_EQ(list_size(htab_list(htab)), i);
		ASSERT_EQ(node_key(list_front(htab_list(htab))), i);
	}

	


	// htab_insert(htab, 24);
	// ASSERT_EQ(htab->size, 10);
	// ASSERT_EQ(htab->load_factor, 1);
	// ASSERT_TRUE(list_(htab, 24));


	htab_free(htab);
}

