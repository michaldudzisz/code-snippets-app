#include <iostream>
#include <string>



void performCalculations(int arg) {

	for (int i = 0; i < arg; ++i)

	return;
}



#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

BOOST_PYTHON_MODULE(cpp_logic)
{
	def("performCalculations", performCalculations);
}