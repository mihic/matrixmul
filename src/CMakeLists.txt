cmake_minimum_required (VERSION 2.8.11)
project (MATRIKE)
set (CMAKE_CXX_FLAGS "-O3 -march=native -DNDEBUG -DBOOST_UBLAS_NDEBUG")
find_package( Boost REQUIRED COMPONENTS program_options )
include_directories( ${Boost_INCLUDE_DIRS} )
add_executable(main matrix.h matrix.cpp tests.cpp classic.cpp classic_transposed.cpp recursive.cpp recursive_transposed.cpp strassen.cpp strassen_transposed.cpp tests.cpp correctness_test.cpp)
target_link_libraries(main ${Boost_PROGRAM_OPTIONS_LIBRARY})




