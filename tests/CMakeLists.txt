#
# test_native_byte_order
#
add_executable ( test_native_byte_order
    test_native_byte_order.cpp
)

target_link_libraries( test_native_byte_order
    PRIVATE greeterd_ipc
)

#
# test_request
#
add_executable ( test_request
    test_request.cpp
)

target_link_libraries( test_request
    PRIVATE greeterd_ipc
)

#
# test_response
#
add_executable ( test_response
    test_response.cpp
)

target_link_libraries( test_response
    PRIVATE greeterd_ipc
)

#
# test_flow_mgr
#
add_executable ( test_flow_mgr
    test_flow_mgr.cpp
)

target_link_libraries( test_flow_mgr
    PRIVATE client
)

add_test( NAME native COMMAND $<TARGET_FILE:test_native_byte_order> )
add_test( NAME request COMMAND $<TARGET_FILE:test_request> )
add_test( NAME response COMMAND $<TARGET_FILE:test_response> )
add_test( NAME flow_mgr COMMAND $<TARGET_FILE:test_flow_mgr> )