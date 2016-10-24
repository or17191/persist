#pragma once

#include <memory>
#include <type_traits>

namespace persist{
namespace detail{
namespace list{
	struct node_base{
		using ptr_t = std::shared_ptr<node_base>;

		ptr_t next_ = nullptr;
	};

	template<typename DataType>
	struct node: node_base{
		using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;

		value_t data_;

		node(const DataType& d): node_base{}, data_{d}{};
		node(DataType&& d): node_base{}, data_{d}{};

		template<typename... Args>
		inline static std::shared_ptr<node_base> make(Args&&... args){
			return std::make_shared<node>(
				value_t(std::forward<Args>(args)...));
		}
	};


}
}
}
