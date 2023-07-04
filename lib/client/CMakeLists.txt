add_library( client
    client.cpp
    flow_mgr.cpp
)

target_link_libraries( client
    PUBLIC greeterd_ipc
)