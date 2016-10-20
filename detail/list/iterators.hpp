#pragma once

#include "node.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
namespace detail{
namespace list{

	template<typename Node>
	class list_iterator:
			public boost::iterator_facade<list_iterator<Node>,
																		typename Node::value_t,
																		boost::forward_traversal_tag>{
		private:
			using node_t = Node;
		public:
			explicit list_iterator(node_base* node): node_(node){}
			list_iterator(){}
			inline auto equal(const list_iterator& other) const;
			inline const auto& dereference() const;
			inline void increment();

		private:
			node_base* node_ = nullptr;
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
