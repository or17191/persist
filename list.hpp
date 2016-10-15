#pragma once

#include "detail/list/list_detail.hpp"
#include "detail/list/node.hpp"
#include "detail/list/iterators.hpp"
#include <ostream>

namespace persist{
	template<typename DataType>
	class list{
		private:
			using builder_t = detail::list::list_builder<list>;
			using node_t = detail::list::list_node<DataType>;
		public:
			using value_t = typename node_t::value_t;
			using iterator_t = detail::list::list_iterator<node_t>;
			
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
			size_t size_;


			template<typename... Args>
			void append(iterator_t& pos, Args&&... args);

			iterator_t append_until(iterator_t& pos, iterator_t first, const iterator_t& last);
			void chain(iterator_t& pos, typename node_t::ptr_t node);

			inline const auto& next_from_prev(const iterator_t& prev) const;
			friend class detail::list::list_builder<list>;
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
