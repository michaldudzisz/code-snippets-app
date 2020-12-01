#include <iostream>
#include <string>



void performCalculations(int arg) {

	int a = 0;
	for (int i = 0; i < arg; ++i) {
		a++;
	}

	return;
}



#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

BOOST_PYTHON_MODULE(cpp_logic)
{
	def("performCalculations", performCalculations);
}