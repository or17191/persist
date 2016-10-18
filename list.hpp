#pragma once

#include "detail/list/builder.hpp"
#include <ostream>

namespace persist{
	template<typename DataType>
	class list{
		private:
			using builder_t = detail::list::builder<DataType>;
			using node_t = typename builder_t::node_t;
		public:
			using value_t = typename builder_t::value_t;
			using iterator_t = typename builder_t::iterator_t;
			
			list(): first_{nullptr}, size_{}{}
			list(std::initializer_list<DataType> init): list(init.begin(), init.end()){}
			template<typename InputIt>
			list(InputIt first, const InputIt& last);

			auto end() const {return iterator_t{};}
			auto begin() const {return iterator_t(first_.get());}
			auto size() const {return size_;}

			template<typename... Args>
			inline list emplace(iterator_t it, Args&&... args) const;
			inline list erase(iterator_t it) const;

			template<typename... Args>
			inline list emplace_front(Args&&... args) const{
				return emplace(begin(), std::forward<Args>(args)...);
			}

			inline list erase_front() const{
				return erase(begin());
			}

		private:
			typename node_t::ptr_t first_;
			decltype(builder_t::make().dst_size_) size_;

			list(decltype(builder_t::make().finalize()) builder):
				first_{std::move(builder.dst_)}, size_{builder.dst_size_}{}

			auto make_builder() const{
				return builder_t::make(first_, size_);
			}

	};

	template<typename DataType>
	bool operator==(const list<DataType>& lhs, const list<DataType>& rhs);

	template<typename DataType>
	bool operator!=(const list<DataType>& lhs, const list<DataType>& rhs){
		return !(lhs == rhs);
	}

	template<typename DataType>
	std::ostream& operator<<(std::ostream& stream, const list<DataType>& list);
}

# include "list.inc"
