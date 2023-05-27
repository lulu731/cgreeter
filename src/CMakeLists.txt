include_directories( ${CMAKE_SOURCE_DIR}/include )

set( SRCS
     main.cpp
)

add_executable ( cgreeter
    ${SRCS}
)