add_executable ( cgreeter
    main.cpp )

target_link_libraries( cgreeter
    PRIVATE greeterd_ipc )
