cmake_minimum_required(VERSION 2.8.3)

PYTHON_ADD_MODULE(cpp_logic cpp-logic.cpp)
FILE(COPY server.py DESTINATION .)
ADD_TEST(NAME 01-server COMMAND ${PYTHON_EXECUTABLE} server.py)