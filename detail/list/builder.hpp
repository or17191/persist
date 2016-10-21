#pragma once

#include "node.hpp"
#include "iterators.hpp"

namespace persist{
namespace detail{
namespace list{
	struct builder_imp{
		protected:
			using node_ptr_t = node_base::ptr_t;
			inline void append(node_ptr_t&& p);
			builder_imp(size_t size);

		public:
			builder_imp(): builder_imp(0){}
			inline auto& emplace_back(node_ptr_t&& p);
			inline auto&& finalize();

			node_ptr_t dst_;
			node_iterator dst_tail_;
			size_t dst_size_;
	};

	struct coupled_builder_imp: builder_imp{
		coupled_builder_imp(const node_ptr_t& first, size_t size);

		template<typename DataType>
		auto& fast_forward(const list_iterator_base& pos);
		inline auto& skip();
		inline auto& emplace_back(node_ptr_t&& args);
		inline auto&& finalize();

		const_node_iterator src_cur_node_;
	};

	template<typename DataType>
	struct builder{
		using node_t = node<DataType>;
		using node_ptr_t = node_base::ptr_t;
		using iterator_t = list_iterator<node_t>;

		static inline auto make(const node_ptr_t& first, size_t size);
		static inline auto make();

		template<typename InputIt>
		static auto make(InputIt first, const InputIt& last);
	};
}
}
}

#include "builder.inc"
