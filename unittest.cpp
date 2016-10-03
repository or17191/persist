#include "gtest/gtest.h"
#include "list.hpp"
#include <memory>
#include <list>


#define ASSERT_RANGES_EQ(c1,c2) \
	{ \
		using std::begin; using std::end; \
	 	ASSERT_TRUE(std::equal(begin(c1), end(c1), begin(c2), end(c2))); \
	} 


TEST(ListTest, ListTestCreation){
	using std::begin; using std::end;
	const persist::list<int> empty_list;
	ASSERT_EQ(0, empty_list.size());
	std::list<int> reference_list = {1, 2, 3, 4, 5};
	persist::list<int> my_list(reference_list.begin(), reference_list.end());
	ASSERT_EQ(reference_list.size(), my_list.size());
	ASSERT_RANGES_EQ(reference_list,my_list);
	persist::list<int> my_list2 = {1, 2, 3, 4, 5};
	ASSERT_RANGES_EQ(reference_list,my_list2);
	ASSERT_EQ(my_list, my_list2);
}
