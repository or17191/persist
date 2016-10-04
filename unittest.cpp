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

#define CHECK_SIZE(c) \
	{ \
		using std::begin; using std::end; \
		ASSERT_EQ(c.size(), std::distance(begin(c), end(c))); \
	} 

class ListTest: public ::testing::Test{
	public:
		ListTest(): reference_list({1, 2, 3, 4, 5}),
						my_list(reference_list.begin(), reference_list.end()){
		}
		std::list<int> reference_list;
		persist::list<int> my_list;
};

TEST_F(ListTest, ListTestCreation){
	const persist::list<int> empty_list;
	ASSERT_EQ(0, empty_list.size());
	CHECK_SIZE(empty_list);
	ASSERT_EQ(reference_list.size(), my_list.size());
	ASSERT_RANGES_EQ(reference_list,my_list);
	CHECK_SIZE(reference_list);
	CHECK_SIZE(my_list);
	persist::list<int> my_list2 = {1, 2, 3, 4, 5};
	ASSERT_RANGES_EQ(reference_list,my_list2);
	ASSERT_EQ(my_list, my_list2);
	CHECK_SIZE(my_list2);

	auto my_list3 = my_list;
	ASSERT_EQ(my_list, my_list3);
	CHECK_SIZE(my_list3);
}

TEST_F(ListTest, ListTestEmplace){
	
	{
		auto it1 = reference_list.begin();
		std::advance(it1, 3);
		reference_list.emplace(it1, 6);
	}
	decltype(my_list) my_list2;
	{
		auto it = my_list.begin();
		std::advance(it, 3);
		my_list2 = my_list.emplace(it, 6);
	}
	ASSERT_RANGES_EQ(reference_list, my_list2);
	ASSERT_NE(my_list, my_list2);
	CHECK_SIZE(my_list2);
	{
		auto it1 = my_list.begin(), it2 = my_list2.begin();
		ASSERT_NE(it1, it2);
		std::advance(it1, 3);
		std::advance(it2, 4);
		ASSERT_EQ(it1++, it2++);
		ASSERT_EQ(it1++, it2++);
		ASSERT_EQ(my_list.end(), it1);
		ASSERT_EQ(my_list2.end(), it2);
	}
}

TEST_F(ListTest, ListTestErase){
	{
		auto it = reference_list.begin();
		std::advance(it, 3);
		reference_list.erase(it);
	}
	decltype(my_list) my_list2;
	{
		auto it = my_list.begin();
		std::advance(it, 3);
		my_list2 = my_list.erase(it);
	}
	ASSERT_RANGES_EQ(reference_list, my_list2);
	CHECK_SIZE(my_list2);
	ASSERT_NE(my_list, my_list2);
	{
		auto it1 = my_list.begin(), it2 = my_list2.begin();
		ASSERT_NE(it1, it2);
		std::advance(it1, 4);
		std::advance(it2, 3);
		ASSERT_EQ(it1++, it2++);
		ASSERT_EQ(my_list.end(), it1);
		ASSERT_EQ(my_list2.end(), it2);
	}
}

TEST_F(ListTest, ListTestEnd){
	reference_list.emplace_back(1);
	auto my_list2 = my_list.emplace(my_list.end(), 1);
	ASSERT_RANGES_EQ(reference_list,my_list2);
	CHECK_SIZE(my_list2);

	auto it = my_list2.begin();
	std::advance(it, my_list2.size() - 1);

	auto my_list3 = my_list2.erase(it);
	ASSERT_EQ(my_list, my_list3);
	CHECK_SIZE(my_list3);
}

TEST_F(ListTest, ListTestBegin){
	reference_list.emplace_front(1);
	auto my_list2 = my_list.emplace_front(1);
	ASSERT_RANGES_EQ(reference_list,my_list2);
	CHECK_SIZE(my_list2);

	auto my_list3 = my_list2.erase_front();
	ASSERT_EQ(my_list, my_list3);
	CHECK_SIZE(my_list3);
}
