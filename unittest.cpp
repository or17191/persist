#include "gtest/gtest.h"
#include "list.hpp"
#include <memory>
#include <list>




TEST(ListTest, ListTestCreation){
	const persist::list<int> empty_list;
	ASSERT_EQ(0, empty_list.size());
	std::list<int> reference_list = {1, 2, 3, 4, 5};
	persist::list<int> my_list(reference_list.begin(), reference_list.end());
	ASSERT_EQ(reference_list.size(), my_list.size());
	ASSERT_TRUE(std::equal(reference_list.begin(), reference_list.end(), my_list.begin(), my_list.end()));
	persist::list<int> my_list2 = {1, 2, 3, 4, 5};
	ASSERT_TRUE(std::equal(reference_list.begin(), reference_list.end(), my_list2.begin(), my_list2.end()));
}
