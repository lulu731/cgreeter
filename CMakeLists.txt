cmake_minimum_required( VERSION 3.25 FATAL_ERROR )

project( cgreeter )

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_CXX_FLAGS_REPORT
    "-g -O0 -Wall -fprofile-arcs -ftest-coverage"
)

find_program( LCOV_COMMAND NAMES lcov )
find_program( GENHTML_COMMMAND NAMES genhtml )
find_program( MEMORYCHECK_COMMAND NAMES valgrind )

add_subdirectory( lib )
add_subdirectory( src )
add_subdirectory( tests )

add_custom_target( execute_tests
    COMMAND ctest )

add_custom_target( report
    COMMAND mkdir -p report
    COMMAND ${LCOV_COMMAND} -c -d . -o report/coverage.info --exclude '/usr/*'
    COMMAND ${GENHTML_COMMMAND} report/coverage.info -o report
    COMMENT "Building report" )

add_dependencies( report execute_tests )

set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

add_custom_target( memcheck
    COMMAND ctest -T memcheck )