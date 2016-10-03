#include <memory>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>

namespace persist{
	template<typename DataType> class list;
	namespace detail{
		template<typename DataType>
		struct list_node{
			using value_t = std::add_const_t<std::remove_volatile_t<DataType>>;
			using ptr_t = std::shared_ptr<list_node<DataType>>;
			value_t data_;
			ptr_t next_;
			
			list_node(const DataType& d): data_{d}, next_{nullptr}{};
			list_node(DataType&& d): data_{d}, next_{nullptr}{};
			template<typename... Args>
			static decltype(auto) make_node(Args&&... args){
				return std::make_shared<list_node>(DataType(std::forward<Args>(args)...));
			}
		};

		template<typename DataType>
		class list_iterator:
				public boost::iterator_facade<list_iterator<DataType>,
																			typename list_node<DataType>::value_t,
																			boost::forward_traversal_tag>{
			private:
				using node_t = list_node<DataType>;
				explicit list_iterator(node_t* node): node_(node){}
				list_iterator(): node_(nullptr){}
			public:
				auto equal(const list_iterator& other) const{
					return node_ == other.node_;
				}
				const auto& dereference() const{
					return node_->data_;
				}

				void increment(){
					if(node_){
						node_ = node_->next_.get();
					}
				}

				friend class list<DataType>;
			private:
				node_t* node_;
				bool empty() const {return node_ == nullptr;}
		};
	}

	template<typename DataType>
	class list{
		private:
			using node_t = detail::list_node<DataType>;
		public:
			using value_t = typename node_t::value_t;
			using iterator_t = detail::list_iterator<DataType>;
			
			list(): first_{nullptr}, last_{nullptr}, size_{}{}
			template<typename InputIt>
			list(InputIt first, const InputIt& last): list{}{
				for(; first!=last; ++first){
					this->append(*first);
				}
			}
			list(std::initializer_list<DataType> init): list(init.begin(), init.end()){}
			auto end() const {return iterator_t{};}
			auto begin() const {return iterator_t(first_.get());}
			template<typename... Args>
			auto emplace(iterator_t it, Args&&... args) const{
				list ret{};
				auto prev = ret.append_until(begin(), it);
				ret.append(std::forward<Args>(args)...);
				ret.chain(next_from_prev(prev));
				return ret;
			}
			auto size() const{return size_;}
			auto pop(iterator_t it) const{
				list ret{};
				auto prev = ret.append_until(begin(), it);
				ret.chain(next_from_prev(prev));
				return ret;
			}
		private:
			typename node_t::ptr_t first_;
			node_t* last_;
			size_t size_;


			template<typename... Args>
			void append(Args&&... args){
				auto&& node = node_t::make_node(std::forward<Args>(args)...);
				auto& new_last = (!last_) ? first_ : last_->next_;
				new_last = node;
				last_ = new_last.get();
				size_++;
			}

			iterator_t append_until(iterator_t first, const iterator_t& last){
				iterator_t prev;
				for(; first!=last; prev=first++){
					append(*first);
				}
				return prev;
			}

			void chain(typename node_t::ptr_t node){
				std::swap(last_->next_, node);
				for(auto p = last_; p; p = p->next_.get()){
					last_ = p;
					size_++;
				}
			}

			const auto& next_from_prev(const iterator_t& prev) const{
				return (!prev.empty()) ?
						prev.node_->next_ : // prev has a next
						first_; // prev doesn't have a next
			}
	};
};
