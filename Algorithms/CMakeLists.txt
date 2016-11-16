cmake_minimum_required ( VERSION 3.1 )
project ( ALGORITHMS )

set ( CMAKE_CXX_COMPILER g++-5 )
set ( CMAKE_CXX_FLAGS "-std=c++11 -Wall" )

include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/src" )
add_subdirectory ( src )
add_subdirectory ( test )

add_executable ( RunCurrentTest ${CURRENT_TEST} )
target_link_libraries ( RunCurrentTest SearchAndSort )
