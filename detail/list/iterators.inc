
namespace persist{
namespace detail{
namespace list{
	inline auto list_iterator_base::equal(const list_iterator_base& other) const{
		return node_ == other.node_;
	}

	template<typename Node>
	inline const auto& list_iterator<Node>::dereference() const{
		return static_cast<Node*>(node_)->data_;
	}

	inline void list_iterator_base::increment(){
		if(node_){
			node_ = node_->next_.get();
		}
	}

	template<typename Node>
	inline auto list_iterator<Node>::equal(const list_iterator& other) const{
		return static_cast<list_iterator_base const &>(*this).equal(static_cast<list_iterator_base const &>(other));
	}

	template<typename NodePtr>
	inline auto node_iterator_impl<NodePtr>::equal(const node_iterator_impl& other) const{
		return node_ == other.node_;
	}

	template<typename NodePtr>
	inline auto& node_iterator_impl<NodePtr>::dereference() const{
		return *node_;
	}

	template<typename NodePtr>
	inline void node_iterator_impl<NodePtr>::increment(){
		if(valid()){
			node_ = std::addressof((*node_)->next_);
		}
	}

	template<typename NodePtr>
	inline bool node_iterator_impl<NodePtr>::valid() const{
		return node_ != nullptr && (*node_) != nullptr;
	}

	template<typename NodePtr>
	bool operator==(const node_iterator_impl<NodePtr>& lhs, const list_iterator_base& rhs){
		using common_t = node_base const * const;
		return static_cast<common_t>(lhs) == static_cast<common_t>(rhs);
	}

	template<typename NodePtr>
	bool operator!=(const node_iterator_impl<NodePtr>& lhs, const list_iterator_base& rhs){
		return !(lhs == rhs);
	}
}
}
}
