#pragma once

#include <memory>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
	template<typename DataType> class list;
	namespace detail{
		template<typename DataType>
		struct list_node{
			using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;
			using ptr_t = std::shared_ptr<list_node<DataType>>;
			value_t data_;
			ptr_t next_;
			
			list_node(const DataType& d): data_{d}, next_{nullptr}{};
			list_node(DataType&& d): data_{d}, next_{nullptr}{};
			template<typename... Args>
			inline static decltype(auto) make_node(Args&&... args){
				return std::make_shared<list_node>(
					DataType(std::forward<Args>(args)...));
			}
		};

		template<typename DataType>
		class list_iterator:
				public boost::iterator_facade<list_iterator<DataType>,
																			typename list_node<DataType>::value_t,
																			boost::forward_traversal_tag>{
			private:
				using node_t = list_node<DataType>;
				explicit list_iterator(node_t* node): node_(node){}
				list_iterator(): node_(nullptr){}
			public:
				auto equal(const list_iterator& other) const{
					return node_ == other.node_;
				}
				const auto& dereference() const{
					return node_->data_;
				}

				void increment(){
					if(node_){
						node_ = node_->next_.get();
					}
				}

				friend class list<DataType>;
			private:
				node_t* node_;
				bool empty() const {return node_ == nullptr;}
		};
	}
}
