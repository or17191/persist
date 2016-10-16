#pragma once

namespace persist{
	template<typename DataType>
	template<typename InputIt>
	list<DataType>::list(InputIt first, const InputIt& last):
		list{detail::list::build_from_sequence<list, DataType>(first, last)}{}

	template<typename DataType>
	template<typename... Args>
	inline list<DataType> list<DataType>::emplace(iterator_t it, Args&&... args) const{
		return list{make_builder().
								fast_forward(it).
								emplace_back(std::forward<Args>(args)...).
								finalize()};
	}

	template<typename DataType>
	inline list<DataType> list<DataType>::erase(iterator_t it) const{
		return list{make_builder().
								fast_forward(it).
								skip().
								finalize()};
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
