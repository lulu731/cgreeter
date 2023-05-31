include_directories( ${CMAKE_SOURCE_DIR}/include )

find_package( Boost REQUIRED COMPONENTS unit_test_framework )

set( SRCS
     test_native_byte_order.cpp
     ${CMAKE_SOURCE_DIR}/src/native_byte_order.cpp
     test_request.cpp
     ${CMAKE_SOURCE_DIR}/src/request.cpp
     test_response.cpp
     ${CMAKE_SOURCE_DIR}/src/response.cpp
)

add_executable ( test
    ${SRCS}
)

target_link_libraries( test PRIVATE ${Boost_LIBRARIES} )