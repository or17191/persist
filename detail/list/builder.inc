#pragma once


namespace persist{
namespace detail{
namespace list{
		template<typename DataType>
		builder<DataType>::builder(const node_ptr_t& src, size_t size):
				src_cur_node_{src},
				dst_{},
				dst_tail_{dst_},
				dst_size_{size}{}

		template<typename DataType>
		builder<DataType>::builder():
				src_cur_node_{},
				dst_{},
				dst_tail_{dst_},
				dst_size_{0}{}

		template<typename DataType>
		builder<DataType>& builder<DataType>::fast_forward(iterator_t pos){
			for(; src_cur_node_!=pos; ++src_cur_node_){
				append(src_cur_node_.value());
			}
			return *this;
		}

		template<typename DataType>
		inline builder<DataType>& builder<DataType>::skip(){
			++src_cur_node_;
			dst_size_--;
			return *this;
		}


		template<typename DataType>
		template<typename... Args>
		inline builder<DataType>& builder<DataType>::emplace_back(Args&&... args){
			append(std::forward<Args>(args)...);
			dst_size_++;
			return *this;
		}

		template<typename DataType>
		inline builder<DataType>&& builder<DataType>::finalize(){
			if(src_cur_node_.valid()){
				*dst_tail_ = *src_cur_node_;
			}	
			return std::move(*this);
		}

		template<typename DataType>
		template<typename... Args>
		inline builder<DataType>& builder<DataType>::append(Args&&... args){
			decltype(auto) node_p = node_t::make_node(std::forward<Args>(args)...);
			*dst_tail_ = node_p;
			++dst_tail_;
			return *this;
		}
}
}
}
