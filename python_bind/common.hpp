#pragma once

#include <pybind11/pybind11.h>
#include <string>


inline std::string repr(const pybind11::object & obj){
	return obj.attr("__repr__").cast<pybind11::object>()().cast<pybind11::str>();
}

inline bool eq(const pybind11::object & lhs, const pybind11::object & rhs){
	return lhs.attr("__eq__").cast<pybind11::object>()(rhs).cast<pybind11::bool_>();
}

inline bool ne(const pybind11::object & lhs, const pybind11::object & rhs){
	return !eq(lhs, rhs);
}

class obj_iterator: public pybind11::iterator{
public:
	using pybind11::iterator::iterator;
	inline object operator*() const{
		return pybind11::object(*static_cast<const pybind11::iterator&>(*this), true);
	}
};
