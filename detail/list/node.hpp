#pragma once

#include <memory>
#include <type_traits>

namespace persist{
namespace detail{
namespace list{
	template<typename DataType>
	struct list_node{
		using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;
		using ptr_t = std::shared_ptr<list_node<DataType>>;
		value_t data_;
		ptr_t next_;
		
		list_node(const DataType& d): data_{d}, next_{nullptr}{};
		list_node(DataType&& d): data_{d}, next_{nullptr}{};

		template<typename... Args>
		inline static decltype(auto) make_node(Args&&... args){
			return std::make_shared<list_node>(
				value_t(std::forward<Args>(args)...));
		}
	};


}
}
}
