#pragma once

namespace persist{
	template<typename DataType>
	template<typename InputIt>
	list<DataType>::list(InputIt first, const InputIt& last): list{}{
		builder_t builder;
		for(; first!=last; ++first){
			builder.append(*first);
		}
		(*this) = builder.finalize();
	}

	template<typename DataType>
	template<typename... Args>
	inline list<DataType> list<DataType>::emplace(iterator_t it, Args&&... args) const{
		builder_t builder{*this};
		builder.append(std::forward<Args>(args)...);
		return list{builder.finalize()};
	}

	template<typename DataType>
	inline list<DataType> list<DataType>::erase(iterator_t it) const{
		builder_t builder(*this);
		return list{builder.fast_forward(it).skip().finalize()};
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
