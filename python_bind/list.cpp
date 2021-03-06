#include "list.hpp"
#include "common.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <sstream>

namespace py=pybind11;
using list_t=persist::list<py::object>;

namespace persist{
template<>
bool operator==<py::object>(const list<py::object>& lhs, const list<py::object>& rhs){
	if(lhs.size() != rhs.size()){
		return false;
	}
	for(auto it_l=lhs.begin(), it_r=rhs.begin();
				it_l!=lhs.end(); ++it_l, ++it_r){
		if(it_l == it_r){
			return true;
		} else if(!eq(*it_l, *it_r)){
			return false;
		}
	}
	return true;
}

template<>
std::ostream& operator<< <py::object>(std::ostream& stream, const list<py::object>& lst){
	stream << "[";
	auto pos = lst.begin(), end = lst.end();
	if(pos!=end){
		stream << repr(*pos);
		++pos;
	}
	for(; pos!=end; ++pos){
		stream << ", " << repr(*pos);
	}
	stream << "]";
	return stream;
}
}

void create_list(py::module& m){
	auto lst = py::class_<list_t>(m, "List");
	lst.def(py::init<>());
	lst.def("__init__",
		[](list_t& instance, const py::iterable& it)
		{ new (&instance) list_t(
				obj_iterator(it.begin()),
				obj_iterator(it.end()));});
	lst.def("__len__", &list_t::size);
	lst.def("__repr__",
		[](const list_t& lst)
		{std::ostringstream ret; ret << "List(" << lst << ')';
		return ret.str();});
	lst.def("__iter__",
		[](const list_t& lst)
			{return py::make_iterator(lst.begin(), lst.end());},
		py::keep_alive<0, 1>());
	lst.def(py::self==py::self);
}
