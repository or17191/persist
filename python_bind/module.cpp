#include <python3.5/pybind11/pybind11.h>

namespace py=pybind11;

void create_list(py::module& m);

PYBIND11_PLUGIN(pyrsist){
	py::module m("pyrsist", "Python bindings for the persist c++ package");

	create_list(m);

	return m.ptr();
}
