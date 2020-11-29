find_package(
  Boost COMPONENTS system filesystem unit_test_framework REQUIRED
)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(Test test.cpp)

target_link_libraries(Test 
  Example
)


