#pragma once

#include "list_detail.hpp"

namespace persist{
	template<typename DataType>
	class list{
		private:
			using node_t = detail::list_node<DataType>;
		public:
			using value_t = typename node_t::value_t;
			using iterator_t = detail::list_iterator<DataType>;
			
			list(): first_{nullptr}, last_{nullptr}, size_{}{}
			list(std::initializer_list<DataType> init): list(init.begin(), init.end()){}
			template<typename InputIt>
			list(InputIt first, const InputIt& last);

			auto end() const {return iterator_t{};}
			auto begin() const {return iterator_t(first_.get());}
			auto size() const{return size_;}

			template<typename... Args>
			inline list emplace(iterator_t it, Args&&... args) const;
			inline list pop(iterator_t it) const;

		private:
			typename node_t::ptr_t first_;
			node_t* last_;
			size_t size_;


			template<typename... Args>
			void append(Args&&... args);

			iterator_t append_until(iterator_t first, const iterator_t& last);
			void chain(typename node_t::ptr_t node);

			inline const auto& next_from_prev(const iterator_t& prev) const;
	};

	template<typename DataType>
	bool operator==(const list<DataType>& lhs, const list<DataType>& rhs);
}

# include "list.inc"
