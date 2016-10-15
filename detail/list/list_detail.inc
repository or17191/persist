#pragma once


namespace persist{
namespace detail{
namespace list{
		template<typename List>
		list_builder<List>::list_builder(const list_t& src):
				src_cur_node_{src.first_},
				dst_{},
				dst_tail_{dst_.first_},
				dst_size_{src.size_}{}

		template<typename List>
		list_builder<List>::list_builder():
				src_cur_node_{},
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
		inline list_builder<List>& list_builder<List>::emplace_back(Args&&... args){
			append(std::forward<Args>(args)...);
			dst_size_++;
			return *this;
		}

		template<typename List>
		inline typename list_builder<List>::list_t&& list_builder<List>::finalize(){
			if(src_cur_node_.valid()){
				*dst_tail_ = *src_cur_node_;
			}	
			dst_.size_ = dst_size_;
			return std::move(dst_);
		}

		template<typename List>
		template<typename... Args>
		inline list_builder<List>& list_builder<List>::append(Args&&... args){
			decltype(auto) node_p = node_t::make_node(std::forward<Args>(args)...);
			*dst_tail_ = node_p;
			++dst_tail_;
			return *this;
		}
}
}
}
