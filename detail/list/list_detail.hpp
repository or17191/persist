#pragma once

#include "iterators.hpp"

namespace persist{
template<typename DataType> class list;
namespace detail{
namespace list{
	template<typename List>
	class list_builder{
		public:
			using list_t = List;
			using value_iterator_t = typename list_t::iterator_t;
			list_builder(const list_t& src);
			list_builder();
			list_builder& fast_forward(value_iterator_t pos);
			inline list_builder& skip();
			template<typename... Args>
			inline list_builder& emplace_back(Args&&... args);
			inline list_t&& finalize();
		private:
			using node_t = typename list_t::node_t;
			using node_ptr_t = typename node_t::ptr_t;
			template<typename T>
			using node_iterator_t=node_iterator<T>;
			node_iterator_t<const node_ptr_t> src_cur_node_;
			list_t dst_;
			node_iterator_t<node_ptr_t> dst_tail_;
			//decltype(dst_.size_) dst_size_;
			size_t dst_size_;

			template<typename... Args>
			inline list_builder& append(Args&&... args);
	};
}
}
}

#include "list_detail.inc"
