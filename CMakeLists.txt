project( cgreeter )

cmake_minimum_required( VERSION 3.21 FATAL_ERROR )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include( CTest )

include_directories( ${CMAKE_SOURCE_DIR}/include )

add_subdirectory( ${CMAKE_SOURCE_DIR}/src )
add_subdirectory( ${CMAKE_SOURCE_DIR}/tests )

find_program( LCOV_COMMAND NAMES lcov )
find_program( GENHTML_COMMMAND NAMES genhtml )

add_custom_target( execute_tests
    COMMAND ctest )

add_custom_target( report
    COMMAND mkdir -p report
    COMMAND ${LCOV_COMMAND} -c -d . -o report/coverage.info --exclude '/usr/*'
    COMMAND ${GENHTML_COMMMAND} report/coverage.info -o report
    COMMENT "Building report" )

add_dependencies( report execute_tests )

find_program( MEMORYCHECK_COMMAND NAMES valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

add_custom_target( memcheck
    COMMAND ctest -T memcheck )