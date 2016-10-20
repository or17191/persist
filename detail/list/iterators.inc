
namespace persist{
namespace detail{
namespace list{
	template<typename Node>
	inline auto list_iterator<Node>::equal(const list_iterator& other) const{
		return node_ == other.node_;
	}

	template<typename Node>
	inline const auto& list_iterator<Node>::dereference() const{
		return static_cast<Node*>(node_)->data_;
	}

	template<typename Node>
	inline void list_iterator<Node>::increment(){
		if(node_){
			node_ = node_->next_.get();
		}
	}

	template<typename NodePtr>
	inline auto node_iterator<NodePtr>::equal(const node_iterator& other) const{
		return node_ == other.node_;
	}

	template<typename NodePtr>
	template<typename OtherNode>
	inline node_iterator<NodePtr>::operator
			list_iterator<OtherNode>() const{
		using list_iterator_t = list_iterator<OtherNode>;
		return valid() ? list_iterator_t{node_->get()} : list_iterator_t{};
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
	inline bool node_iterator<NodePtr>::valid() const{
		return node_ != nullptr && (*node_) != nullptr;
	}
}
}
}
