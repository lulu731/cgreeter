include_directories( ${CMAKE_SOURCE_DIR} )

set( SRCS
     main.cpp
     native_byte_order.cpp
)

add_executable ( cgreeter
    ${SRCS}
)