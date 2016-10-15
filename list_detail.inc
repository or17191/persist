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

		template<typename Node>
		inline auto node_iterator<Node>::equal(const node_iterator& other) const{
			return node_ == other.node_;
		}

		template<typename Node>
		template<typename T>
		inline node_iterator<Node>::operator list_iterator<T>() const{
			using list_iterator_t = list_iterator<T>;
			return valid() ? list_iterator_t{(*node_).get()} : list_iterator_t{};
		}

		template<typename Node>
		inline auto& node_iterator<Node>::dereference() const{
			return *node_;
		}

		template<typename Node>
		inline void node_iterator<Node>::increment(){
			if(valid()){
				node_ = std::addressof((*node_)->next_);
			}
		}

		template<typename Node>
		inline auto& node_iterator<Node>::value() const{
			return (*node_)->data_;
		}

		template<typename Node>
		inline auto node_iterator<Node>::valid() const{
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
				src_cur_node_{nullptr},
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
		inline list_builder<List>& list_builder<List>::append(Args&&... args){
			auto&& node_p = make_node<node_t>(std::forward<Args>(args)...);
			*dst_tail_ = node;
			++dst_tail_;
			dst_size_++;
			return *this;
		}

		template<typename List>
		inline list_t&& list_builder<List>::finalize(){
			*dst_tail = *src_cur_node_;
			dst_.size_ = dst_size_;
			return std::move(dst_);
		}

	}
}

