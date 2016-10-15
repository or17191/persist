#pragma once

#include <memory>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
	template<typename DataType> class list;
	template<typename DataType> class list_builder;
	namespace detail{
		template<typename DataType>
		struct list_node{
			using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;
			using ptr_t = std::shared_ptr<list_node<DataType>>;
			value_t data_;
			ptr_t next_;
			
			list_node(const DataType& d): data_{d}, next_{nullptr}{};
			list_node(DataType&& d): data_{d}, next_{nullptr}{};
		};

		template<typename Node, typename... Args>
		decltype(auto) make_node(Args&&... args);

		template<typename DataType>
		class list_iterator:
				public boost::iterator_facade<list_iterator<DataType>,
																			typename list_node<DataType>::value_t,
																			boost::forward_traversal_tag>{
			private:
				using node_t = list_node<DataType>;
			public:
				explicit list_iterator(node_t* node): node_(node){}
				list_iterator(): node_(nullptr){}
				inline auto equal(const list_iterator& other) const;
				inline const auto& dereference() const;
				inline void increment();

				friend class list<DataType>;
				friend class list_builder<DataType>;
			private:
				node_t* node_;
				inline bool empty() const;
		};


		template<typename NodePtr>
		class node_iterator:
				public boost::iterator_facade<node_iterator<NodePtr>,
																			NodePtr,
																			boost::forward_traversal_tag>{
			private:
				using node_ptr_t = NodePtr;
			public:
				explicit node_iterator(node_ptr_t& node): node_(std::addressof(node)){}
				node_iterator(): node_(nullptr){}
				inline auto equal(const node_iterator& other) const;
				inline auto& dereference() const;
				inline void increment();
				inline auto& value() const;
				inline bool valid() const;

				template<typename T>
				inline operator list_iterator<T>() const;

			private:
				node_ptr_t* node_;

		};

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

#include "list_detail.inc"
