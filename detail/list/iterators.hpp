#pragma once

#include "node.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
namespace detail{
namespace list{
	class list_iterator_base{
		public:
			explicit list_iterator_base(node_base* node): node_(node){}
			list_iterator_base(){}
			inline auto equal(const list_iterator_base& other) const;
			inline void increment();

		protected:
			node_base* node_ = nullptr;

	};

	template<typename Node>
	class list_iterator:
			public list_iterator_base,
			public boost::iterator_facade<list_iterator<Node>,
																		typename Node::value_t,
																		boost::forward_traversal_tag>{
		private:
			using node_t = Node;
		public:
			using list_iterator_base::list_iterator_base;
			inline const auto& dereference() const;
			inline auto equal(const list_iterator& other) const;
	};

	template<typename NodePtr>
	class node_iterator_impl:
			public boost::iterator_facade<node_iterator_impl<NodePtr>,
																		NodePtr,
																		boost::forward_traversal_tag>{
		private:
			using node_ptr_t = NodePtr;
			using node_t = typename node_ptr_t::element_type;
		public:
			explicit node_iterator_impl(node_ptr_t& node): node_(std::addressof(node)){}
			node_iterator_impl(){}
			inline auto equal(const node_iterator_impl& other) const;
			inline auto& dereference() const;
			inline void increment();
			inline bool valid() const;

			template<typename OtherNode>
			inline operator list_iterator<OtherNode>() const;

		private:
			node_ptr_t* node_ = nullptr;

	};

	using node_iterator = node_iterator_impl<node_base::ptr_t>;
	using const_node_iterator = node_iterator_impl<const node_base::ptr_t>;

}
}
}

#include "iterators.inc"
