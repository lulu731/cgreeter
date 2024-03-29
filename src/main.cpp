
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "include/client.hpp"
#include "include/native_byte_order.hpp"

#if defined( BOOST_ASIO_HAS_LOCAL_SOCKETS )


int main( int argc, char* argv[] )
{
    const std::string CmdOpt{ "--cmd" };
    const std::string Argv1{ argv[1] };
    if( Argv1 == CmdOpt )
    {
        const std::string Cmd{ argv[2] };
        while( true )
        {
            {
                std::cout << "Welcome to cgreeter !" << std::endl;
                std::cout << "-*-*-*-*-*-*-*-*-*-*-" << std::endl;
                std::cout << std::endl;

                GREETD_CLIENT client;
                std::string   username;
                std::cout << "Enter username: ";
                std::cin >> username;
                client.InitFlowMgr( username );
                client.Connect();

                client.CommunicateWithServer();

                if( client.GetResponse()->IsAuthMessage() )
                {
                    std::cout << client.GetResponse()->GetFieldDescription() << " ";
                    std::string password;
                    std::cin >> password;
                    client.SetPassword( password );
                    client.CommunicateWithServer();

                    if( client.GetResponse()->IsSuccess() )
                    {
                        const std::vector<std::string> aCommand{ Cmd };
                        client.StartSession( aCommand );
                        client.CommunicateWithServer();
                        return EXIT_SUCCESS;
                    }
                    else
                    {
                        std::cout << client.GetResponse()->GetFieldType() << " "
                                  << client.GetResponse()->GetFieldDescription() << std::endl;
                        return EXIT_FAILURE;
                    }
                }
            }
        }
        return EXIT_FAILURE;
    }
}

#else  // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
std::scout
        << "BOOST_ASIO_HAS_LOCAL_SOCKETS not defined\n"; // error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)