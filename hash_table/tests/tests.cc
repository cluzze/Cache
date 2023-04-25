#include "hash_table.h"

#include <gtest/gtest.h>

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

TEST(hash_table, create)
{
	htab_t *htab = htab_create(10);
}