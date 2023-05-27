include_directories( ${CMAKE_SOURCE_DIR}/include )

find_package( Boost REQUIRED COMPONENTS unit_test_framework )

set( SRCS
     test_native_byte_order.cpp
)

add_executable ( test
    ${SRCS}
)

target_link_libraries( test PRIVATE ${Boost_LIBRARIES} )