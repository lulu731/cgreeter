include_directories( ${CMAKE_SOURCE_DIR}/include )

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