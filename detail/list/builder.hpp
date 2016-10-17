#pragma once

#include "node.hpp"
#include "iterators.hpp"

namespace persist{
template<typename DataType> class list;
namespace detail{
namespace list{
	template<typename DataType>
	struct builder{
		using node_t = node<DataType>;
		using node_ptr_t = typename node_t::ptr_t;
		using value_t = typename node_t::value_t;
		using iterator_t = list_iterator<node_t>;

		builder(const node_ptr_t& first, size_t size);
		builder();

		template<typename InputIt>
		builder(InputIt first, const InputIt& last);

		builder& fast_forward(iterator_t pos);
		inline builder& skip();
		template<typename... Args>
		inline builder& emplace_back(Args&&... args);
		inline builder&& finalize();

		node_iterator<const node_ptr_t> src_cur_node_;
		node_ptr_t dst_;
		node_iterator<node_ptr_t> dst_tail_;
		size_t dst_size_;

		template<typename... Args>
		inline builder& append(Args&&... args);
	};

}
}
}

#include "builder.inc"
