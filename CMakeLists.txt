project( cgreeter )

cmake_minimum_required( VERSION 3.21 FATAL_ERROR )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include( CTest )

include_directories( ${CMAKE_SOURCE_DIR}/include )

add_subdirectory( ${CMAKE_SOURCE_DIR}/src )
add_subdirectory( ${CMAKE_SOURCE_DIR}/tests )