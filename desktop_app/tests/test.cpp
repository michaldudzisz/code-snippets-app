#define BOOST_TEST_MODULE example_tests

#include <boost/test/included/unit_test.hpp>
#include "example.h"

BOOST_AUTO_TEST_CASE(example_test) {
  BOOST_CHECK(1 == 1);
}

BOOST_AUTO_TEST_CASE(add_test) {
    BOOST_CHECK_EQUAL(add(3,1), 4);
}

