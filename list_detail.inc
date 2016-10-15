#pragma once

#include <memory>

namespace persist{
	namespace detail{
		template<typename Node, typename... Args>
		inline decltype(auto) make_node(Args&&... args){
			return std::make_shared<Node>(
				typename Node::value_t(std::forward<Args>(args)...));
		}

		template<typename DataType>
		inline auto list_iterator<DataType>::equal(const list_iterator& other) const{
			return node_ == other.node_;
		}

		template<typename DataType>
		inline const auto& list_iterator<DataType>::dereference() const{
			return node_->data_;
		}

		template<typename DataType>
		inline void list_iterator<DataType>::increment(){
			if(node_){
				node_ = node_->next_.get();
			}
		}

		template<typename DataType>
		inline bool list_iterator<DataType>::empty() const{
			return node_ == nullptr;
		}

		template<typename NodePtr>
		inline auto node_iterator<NodePtr>::equal(const node_iterator& other) const{
			return node_ == other.node_;
		}

		template<typename NodePtr>
		template<typename T>
		inline node_iterator<NodePtr>::operator list_iterator<T>() const{
			using list_iterator_t = list_iterator<T>;
			return valid() ? list_iterator_t{(*node_).get()} : list_iterator_t{};
		}

		template<typename NodePtr>
		inline auto& node_iterator<NodePtr>::dereference() const{
			return *node_;
		}

		template<typename NodePtr>
		inline void node_iterator<NodePtr>::increment(){
			if(valid()){
				node_ = std::addressof((*node_)->next_);
			}
		}

		template<typename NodePtr>
		inline auto& node_iterator<NodePtr>::value() const{
			return (*node_)->data_;
		}

		template<typename NodePtr>
		inline bool node_iterator<NodePtr>::valid() const{
			return node_ != nullptr && (*node_) != nullptr;
		}

		template<typename List>
		list_builder<List>::list_builder(const list_t& src):
				src_cur_node_{src.first_},
				dst_{},
				dst_tail_{dst_.first_},
				dst_size_{src.size_}{}

		template<typename List>
		list_builder<List>::list_builder():
				src_cur_node_{},
				dst_{},
				dst_tail_{dst_.first_},
				dst_size_{0}{}

		template<typename List>
		list_builder<List>& list_builder<List>::fast_forward(value_iterator_t pos){
			for(; src_cur_node_!=pos; ++src_cur_node_){
				append(src_cur_node_.value());
			}
			return *this;
		}

		template<typename List>
		inline list_builder<List>& list_builder<List>::skip(){
			++src_cur_node_;
			dst_size_--;
			return *this;
		}


		template<typename List>
		template<typename... Args>
		inline list_builder<List>& list_builder<List>::emplace_back(Args&&... args){
			append(std::forward<Args>(args)...);
			dst_size_++;
			return *this;
		}

		template<typename List>
		inline typename list_builder<List>::list_t&& list_builder<List>::finalize(){
			if(src_cur_node_.valid()){
				*dst_tail_ = *src_cur_node_;
			}	
			dst_.size_ = dst_size_;
			return std::move(dst_);
		}

		template<typename List>
		template<typename... Args>
		inline list_builder<List>& list_builder<List>::append(Args&&... args){
			decltype(auto) node_p = make_node<node_t>(std::forward<Args>(args)...);
			*dst_tail_ = node_p;
			++dst_tail_;
			return *this;
		}

	}
}

