
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "include/client.hpp"
#include "include/native_byte_order.hpp"

#if defined( BOOST_ASIO_HAS_LOCAL_SOCKETS )


int main( int argc, char* argv[] )
{
    /*std::cout << "argc = " << argc << std::endl;
    std::cout << "argv[] = " << *argv << std::endl;
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    std::cout << argv[3] << std::endl;
    std::cout << argv[10] << std::endl;*/

    const std::string CmdOpt{ "--cmd" };
    const std::string Argv1{ argv[1] };
    if( Argv1 == CmdOpt )
    {
        const std::string Cmd{ argv[2] };
        while( true )
        {
            {
                GREETD_CLIENT client;
                std::string   username;
                std::cout << "Enter username: ";
                std::cin >> username;
                client.InitFlowMgr( username );
                client.SendRequestToServer();
                client.GetResponseFmServer();

                if( client.GetResponse()->IsAuthMessage() )
                {
                    std::cout << "Enter password: ";
                    std::string password;
                    std::cin >> password;
                    client.SetPassword( password );
                    client.UpdateFlow();
                    client.SendRequestToServer();
                    client.GetResponseFmServer();

                    if( client.GetResponse()->IsSuccess() )
                    {
                        std::cout << "Authentication successful" << std::endl;
                        return EXIT_SUCCESS;
                    }
                }
                client.SendRequestToServer(); //Error : should be a cancel request
            }
        }
        return EXIT_FAILURE;
    }
}
/*else
    {
        std::cout << "Authentication failed" << std::endl;
    }

    else
    {
        std::cout << "Authentication failed" << std::endl;
    }
*/


#else  // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
std::scout
        << "BOOST_ASIO_HAS_LOCAL_SOCKETS not defined\n"; // error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)