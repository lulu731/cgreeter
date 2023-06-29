add_library( greeterd_ipc
    native_byte_order.cpp
    request.cpp
    response.cpp )

target_include_directories ( greeterd_ipc
    PUBLIC ${CMAKE_SOURCE_DIR} )