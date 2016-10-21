#pragma once

#include "node.hpp"
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
namespace detail{
namespace list{
	template<typename NodePtr>
	class node_iterator_impl;

	class list_iterator_base;

	template<typename NodePtr>
	bool inline operator==(const node_iterator_impl<NodePtr>& lhs, const list_iterator_base& rhs);

	class list_iterator_base{
		public:
			explicit inline list_iterator_base(node_base* node): node_(node){}
			inline list_iterator_base(){}
			inline auto equal(const list_iterator_base& other) const;
			inline void increment();

			template<typename NodePtr>
			friend bool operator==(const node_iterator_impl<NodePtr>& lhs, const list_iterator_base& rhs);

		protected:
			node_base* node_ = nullptr;

		private:
			inline operator node_base const * () const{return node_;}
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
		public:
			explicit node_iterator_impl(node_ptr_t& node): node_(std::addressof(node)){}
			inline node_iterator_impl(){}
			inline auto equal(const node_iterator_impl& other) const;
			inline auto& dereference() const;
			inline void increment();
			inline bool valid() const;

			friend bool operator==<>(const node_iterator_impl& lhs, const list_iterator_base& rhs);

		private:
			node_ptr_t* node_ = nullptr;

			operator node_base const * () const{return valid() ? node_->get(): nullptr;}

	};

	using node_iterator = node_iterator_impl<node_base::ptr_t>;
	using const_node_iterator = node_iterator_impl<const node_base::ptr_t>;

	template<typename NodePtr>
	inline bool operator!=(const node_iterator_impl<NodePtr>& lhs, const list_iterator_base& rhs);

}
}
}

#include "iterators.inc"
