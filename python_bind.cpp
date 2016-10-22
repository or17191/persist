#include "list.hpp"
#include <python2.7/pybind11/pybind11.h>
#include <sstream>
#include <memory>

namespace py=pybind11;
using list_t = persist::list<py::object>;

std::string repr(const py::object & obj){
	return obj.attr("__repr__").cast<py::object>()().cast<py::str>();
}

class obj_iterator: public py::iterator{
public:
	using py::iterator::iterator;
	object operator*() const{
		return py::object(*static_cast<const py::iterator&>(*this), true);
	}
};

auto list_repr(const list_t& lst){
	std::ostringstream ret;
	ret << "List([";
	auto pos = lst.begin(), end = lst.end();
	if(pos!=end){
		ret << repr(*pos);
		pos++;
	}
	for(; pos!=end; pos++){
		ret << ", " << repr(*pos);
	}
	ret << "])";
	return ret.str();
}

PYBIND11_PLUGIN(pyrsist){
	py::module m("pyrsist", "Python bindings for the persist c++ package");

	auto lst = py::class_<list_t>(m, "List");
	lst.def(py::init<>());
	lst.def("__init__",
		[](list_t& instance, const py::iterable& it)
		{ new (&instance) list_t(
				obj_iterator(it.begin()),
				obj_iterator(it.end()));});
	lst.def("__len__", &list_t::size);
	lst.def("__repr__", &list_repr);
	lst.def("__iter__",
		[](const list_t& lst)
			{return py::make_iterator(lst.begin(), lst.end());},
		py::keep_alive<0, 1>());

	return m.ptr();
}
