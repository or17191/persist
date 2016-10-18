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

		struct builder_imp;
		struct coupled_builder_imp;

		static inline auto make(const node_ptr_t& first, size_t size);
		static inline auto make();

		template<typename InputIt>
		static auto make(InputIt first, const InputIt& last);
	};

	template<typename DataType>
	struct builder<DataType>::builder_imp{
		builder_imp();
		template<typename... Args>
		inline auto& emplace_back(Args&&... args);
		inline auto&& finalize();
		
		node_ptr_t dst_;
		node_iterator<node_ptr_t> dst_tail_;
		size_t dst_size_;

		protected:
			template<typename... Args>
			inline void append(Args&&... args);
	};

	template<typename DataType>
	struct builder<DataType>::coupled_builder_imp: public builder_imp{
		using builder_imp::builder_imp;
		coupled_builder_imp(const node_ptr_t& first, size_t size);
		auto& fast_forward(iterator_t pos);
		inline auto& skip();
		template<typename... Args>
		inline auto& emplace_back(Args&&... args);
		inline auto&& finalize();

		node_iterator<const node_ptr_t> src_cur_node_;
	};
}
}
}

#include "builder.inc"
