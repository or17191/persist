#pragma once


namespace persist{
namespace detail{
namespace list{
		builder_imp::builder_imp(size_t size):
				dst_{},
				dst_tail_{dst_},
				dst_size_{size}{}

		inline auto& builder_imp::emplace_back(builder_imp::node_ptr_t&& p){
			append(std::move(p));
			dst_size_++;
			return *this;
		}

		inline void builder_imp::append(builder_imp::node_ptr_t&& p){
			*dst_tail_ = std::move(p);
			++dst_tail_;
		}
		
		inline auto&& builder_imp::finalize(){
			return std::move(*this);
		}

		coupled_builder_imp::coupled_builder_imp
					(const coupled_builder_imp::node_ptr_t& src, size_t size):
				builder_imp{size},
				src_cur_node_{src}{}

		template<typename DataType>
		auto& coupled_builder_imp::fast_forward(const list_iterator_base& pos){
			using node_t = node<DataType>;
			for(; src_cur_node_!=pos; ++src_cur_node_){
				auto p = static_cast<node_t const *>(src_cur_node_->get());
				this->append(node_t::make(p->data_));
			}
			return *this;
		}

		inline auto& coupled_builder_imp::skip(){
			++src_cur_node_;
			this->dst_size_--;
			return *this;
		}

		inline auto& coupled_builder_imp::
				emplace_back(coupled_builder_imp::node_ptr_t&& p){
			return static_cast<coupled_builder_imp&>(
				static_cast<builder_imp&>(*this).
				emplace_back(std::move(p)));
		}

		inline auto&& coupled_builder_imp::finalize(){
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
				b.emplace_back(builder::node_t::make(*first));
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
