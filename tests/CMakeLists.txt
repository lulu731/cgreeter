include_directories( ${CMAKE_SOURCE_DIR} )

set( CMAKE_CXX_FLAGS
    "-g -O0 -Wall -fprofile-arcs -ftest-coverage" )

add_executable ( test_native_byte_order
    test_native_byte_order.cpp
    ${CMAKE_SOURCE_DIR}/src/native_byte_order.cpp
)

add_executable ( test_request
    test_request.cpp
    ${CMAKE_SOURCE_DIR}/src/request.cpp
)

add_executable ( test_response
    test_response.cpp
    ${CMAKE_SOURCE_DIR}/src/response.cpp
)

add_executable ( test_flow_mgr
    test_flow_mgr.cpp
    ${CMAKE_SOURCE_DIR}/src/request.cpp
    ${CMAKE_SOURCE_DIR}/src/response.cpp
    ${CMAKE_SOURCE_DIR}/src/flow_mgr.cpp )

add_test( NAME native COMMAND test_native_byte_order )
add_test( NAME request COMMAND test_request )
add_test( NAME response COMMAND test_response )
add_test( NAME flow_mgr COMMAND test_flow_mgr )