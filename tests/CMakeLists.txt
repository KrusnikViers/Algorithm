cmake_minimum_required(VERSION 3.2.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)
enable_testing()
include_directories(googletest/googletest/include googletest/googletest)

set(SRC
	sort_unittest.cpp)
include_directories(../)
add_executable(unit_tests ${SRC})
target_link_libraries(unit_tests gtest gtest_main)
file(COPY data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
