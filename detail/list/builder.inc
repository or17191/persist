#pragma once


namespace persist{
namespace detail{
namespace list{

		template<typename DataType>
		builder<DataType>::builder_imp::builder_imp():
				dst_{},
				dst_tail_{dst_},
				dst_size_{0}{}

		template<typename DataType>
		template<typename... Args>
		inline auto& builder<DataType>::builder_imp::emplace_back(Args&&... args){
			append(std::forward<Args>(args)...);
			dst_size_++;
			return *this;
		}

		template<typename DataType>
		template<typename... Args>
		inline void builder<DataType>::builder_imp::append(Args&&... args){
			decltype(auto) node_p = node_t::make(std::forward<Args>(args)...);
			*dst_tail_ = node_p;
			++dst_tail_;
		}
		
		template<typename DataType>
		inline auto&& builder<DataType>::builder_imp::finalize(){
			return std::move(*this);
		}

		template<typename DataType>
		builder<DataType>::coupled_builder_imp::coupled_builder_imp
					(const node_ptr_t& src, size_t size):
				builder_imp{},
				src_cur_node_{src}{
			this->dst_size_ = size;
		}

		template<typename DataType>
		auto& builder<DataType>::coupled_builder_imp::fast_forward(iterator_t pos){
			for(; src_cur_node_!=pos; ++src_cur_node_){
				this->append(src_cur_node_.value());
			}
			return *this;
		}

		template<typename DataType>
		inline auto& builder<DataType>::coupled_builder_imp::skip(){
			++src_cur_node_;
			this->dst_size_--;
			return *this;
		}

		template<typename DataType>
		template<typename... Args>
		inline auto& builder<DataType>::coupled_builder_imp::
				emplace_back(Args&&... args){
			return static_cast<coupled_builder_imp&>(
				static_cast<builder_imp&>(*this).
				emplace_back(std::forward<Args>(args)...));
		}

		template<typename DataType>
		inline auto&& builder<DataType>::coupled_builder_imp::finalize(){
			if(src_cur_node_.valid()){
				*this->dst_tail_ = *src_cur_node_;
			}	
			return std::move(*this);
		}

		template<typename DataType>
		template<typename InputIt>
		auto builder<DataType>::make(InputIt first,
					const InputIt& last){
			builder_imp b;
			for(; first!=last; ++first){
				b.emplace_back(*first);
			}
			return b;
		}

		template<typename DataType>
		inline auto builder<DataType>::make(){
			return builder_imp();
		}

		template<typename DataType>
		inline auto builder<DataType>::make(const node_ptr_t& first,
				size_t size){
			return coupled_builder_imp{first, size};
		}
}
}
}
