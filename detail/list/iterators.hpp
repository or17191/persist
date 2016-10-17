#pragma once

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
				explicit list_iterator(node_t* node): node_(node){}
				list_iterator(){}
				inline auto equal(const list_iterator& other) const;
				inline const auto& dereference() const;
				inline void increment();

			private:
				node_t* node_ = nullptr;
		};

		template<typename NodePtr>
		class node_iterator:
				public boost::iterator_facade<node_iterator<NodePtr>,
																			NodePtr,
																			boost::forward_traversal_tag>{
			private:
				using node_ptr_t = NodePtr;
				using node_t = typename node_ptr_t::element_type;
			public:
				explicit node_iterator(node_ptr_t& node): node_(std::addressof(node)){}
				node_iterator(){}
				inline auto equal(const node_iterator& other) const;
				inline auto& dereference() const;
				inline void increment();
				inline auto& value() const;
				inline bool valid() const;

				inline operator list_iterator<node_t>() const;

			private:
				node_ptr_t* node_ = nullptr;

		};

}
}
}

#include "iterators.inc"
