add_executable( cgreeter
    main.cpp
)

target_link_libraries( cgreeter
    PRIVATE client )

install( TARGETS cgreeter
         DESTINATION ${CMAKE_INSTALL_BINDIR}
)