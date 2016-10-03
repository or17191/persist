#include "gtest/gtest.h"
#include "list.hpp"
#include <memory>
#include <list>
#include <utility>
#include <iostream>


#define ASSERT_RANGES_EQ(c1,c2) \
	{ \
		using std::begin; using std::end; \
		ASSERT_EQ(c1.size(), c2.size()); \
	 	ASSERT_TRUE(std::equal(begin(c1), end(c1), begin(c2), end(c2))); \
	} 


TEST(ListTest, ListTestCreation){
	const persist::list<int> empty_list;
	ASSERT_EQ(0, empty_list.size());
	std::list<int> reference_list = {1, 2, 3, 4, 5};
	persist::list<int> my_list(reference_list.begin(), reference_list.end());
	ASSERT_EQ(reference_list.size(), my_list.size());
	ASSERT_RANGES_EQ(reference_list,my_list);
	persist::list<int> my_list2 = {1, 2, 3, 4, 5};
	ASSERT_RANGES_EQ(reference_list,my_list2);
	ASSERT_EQ(my_list, my_list2);

	auto my_list3 = my_list;
	ASSERT_EQ(my_list, my_list3);
}

TEST(ListTest, ListTestEmplace){
	std::list<int> reference_list = {1, 2, 3, 4, 5};
	persist::list<int> my_list(reference_list.begin(), reference_list.end());
	ASSERT_RANGES_EQ(reference_list,my_list);

	auto it1 = reference_list.begin();
	std::advance(it1, 3);
	reference_list.emplace(it1, 6);
	auto it2 = my_list.begin();
	std::advance(it2, 3);
	auto my_list2 = my_list.emplace(it2, 6);
	ASSERT_RANGES_EQ(reference_list, my_list2);
	ASSERT_NE(my_list, my_list2);
}

TEST(ListTest, ListTestErase){
	std::list<int> reference_list = {1, 2, 3, 4, 5};
	persist::list<int> my_list(reference_list.begin(), reference_list.end());
	ASSERT_RANGES_EQ(reference_list,my_list);

	auto it1 = reference_list.begin();
	std::advance(it1, 3);
	reference_list.erase(it1);
	auto it2 = my_list.begin();
	std::advance(it2, 3);
	auto my_list2 = my_list.erase(it2);
	ASSERT_RANGES_EQ(reference_list, my_list2);
	ASSERT_NE(my_list, my_list2);
}
