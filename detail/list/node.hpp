#pragma once

#include <memory>
#include <type_traits>

namespace persist{
namespace detail{
namespace list{
	template<typename DataType>
	struct node{
		using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;
		using ptr_t = std::shared_ptr<node>;

		value_t data_;
		ptr_t next_ = nullptr;
		
		node(const DataType& d): data_{d}{};
		node(DataType&& d): data_{d}{};

		template<typename... Args>
		inline static decltype(auto) make_node(Args&&... args){
			return std::make_shared<node>(
				value_t(std::forward<Args>(args)...));
		}
	};


}
}
}
