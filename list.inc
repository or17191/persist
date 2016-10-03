#pragma once

namespace persist{
	template<typename DataType>
	template<typename InputIt>
	list<DataType>::list(InputIt first, const InputIt& last): list<DataType>{}{
		for(; first!=last; ++first){
			append(*first);
		}
	}

	template<typename DataType>
	template<typename... Args>
	inline list<DataType> list<DataType>::emplace(iterator_t it, Args&&... args) const{
		list ret{};
		auto prev = ret.append_until(begin(), it);
		ret.append(std::forward<Args>(args)...);
		ret.chain(next_from_prev(prev));
		return ret;
	}

	template<typename DataType>
	inline list<DataType> list<DataType>::pop(iterator_t it) const{
		list ret{};
		auto prev = ret.append_until(begin(), it);
		ret.chain(next_from_prev(prev));
		return ret;
	}

	template<typename DataType>
	template<typename... Args>
	inline void list<DataType>::append(Args&&... args){
		auto&& node = node_t::make_node(std::forward<Args>(args)...);
		auto& new_last = (!last_) ? first_ : last_->next_;
		new_last = node;
		last_ = new_last.get();
		size_++;
	}

	template<typename DataType>
	typename list<DataType>::iterator_t list<DataType>::append_until(iterator_t first, const iterator_t& last){
		iterator_t prev;
		for(; first!=last; prev=first++){
			append(*first);
		}
		return prev;
	}

	template<typename DataType>
	void list<DataType>::chain(typename node_t::ptr_t node){
		std::swap(last_->next_, node);
		for(auto p = last_; p; p = p->next_.get()){
			last_ = p;
			size_++;
		}
	}

	template<typename DataType>
	inline const auto& list<DataType>::next_from_prev(const list<DataType>::iterator_t& prev) const{
		return (!prev.empty()) ?
				prev.node_->next_ : // prev has a next
				first_; // prev doesn't have a next
	}

	template<typename DataType>
	bool operator==(const list<DataType>& lhs, const list<DataType>& rhs){
		if(lhs.size() != rhs.size()){
			return false;
		}
		for(auto it_l=lhs.begin(), it_r=rhs.begin();
					it_l!=lhs.end(); ++it_l, ++it_r){
			if(it_l == it_r){
				return true;
			} else if(*it_l != *it_r){
				return false;
			}
		}
		return true;
	}
}
