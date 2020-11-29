set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
  Qt5::Widgets
)
