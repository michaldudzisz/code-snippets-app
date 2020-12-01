#include <iostream>
#include <string>



char const* performCalculations() {

	for (int i = 0; i < 10; ++i)

	return "Calculations done!";
}



#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

BOOST_PYTHON_MODULE(cpp_logic)
{
	def("performCalculations", performCalculations);
}