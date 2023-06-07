enable_testing()

include_directories( ${CMAKE_SOURCE_DIR} )

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

add_test( NAME native COMMAND test_native_byte_order )
add_test( NAME request COMMAND test_request )
add_test( NAME response COMMAND test_response )