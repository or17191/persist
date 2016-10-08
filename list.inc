#pragma once

namespace persist{
	template<typename DataType>
	template<typename InputIt>
	list<DataType>::list(InputIt first, const InputIt& last): list<DataType>{}{
		auto pos = end();
		for(; first!=last; ++first){
			append(pos, *first);
		}
	}

	template<typename DataType>
	template<typename... Args>
	inline list<DataType> list<DataType>::emplace(iterator_t it, Args&&... args) const{
		list ret{};
		auto pos = ret.end();
		auto prev = ret.append_until(pos, begin(), it);
		ret.append(pos, std::forward<Args>(args)...);
		ret.chain(pos, next_from_prev(prev));
		ret.size_ = size_ + 1;
		return ret;
	}

	template<typename DataType>
	inline list<DataType> list<DataType>::erase(iterator_t it) const{
		list ret{};
		auto pos = ret.end();
		auto prev = ret.append_until(pos, begin(), it);
		ret.chain(pos, next_from_prev(prev)->next_);
		ret.size_ = size_ - 1;
		return ret;
	}

	template<typename DataType>
	template<typename... Args>
	inline void list<DataType>::append(list<DataType>::iterator_t& pos, Args&&... args){
		auto&& node = node_t::make_node(std::forward<Args>(args)...);
		auto& new_last = (pos.empty()) ? first_ : pos.node_->next_;
		new_last = node;
		size_++;
		pos = iterator_t{node.get()};
	}

	template<typename DataType>
	typename list<DataType>::iterator_t list<DataType>::append_until(iterator_t& pos, iterator_t first, const iterator_t& last){
		iterator_t prev;
		for(; first!=last; prev=first++){
			append(pos, *first);
		}
		return prev;
	}

	template<typename DataType>
	void list<DataType>::chain(iterator_t& pos, typename node_t::ptr_t node){
		if(first_){
			std::swap(pos.node_->next_, node);
		} else{ // empty list
			first_ = node;
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

	template<typename DataType>
	std::ostream& operator<<(std::ostream& stream, const list<DataType>& list){
		stream << '{';
		for(const auto& e: list){
			stream << e << ',' << ' ';
		}
		stream << '}';
		return stream;
	}
}
