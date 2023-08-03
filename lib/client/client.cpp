#include "include/client.hpp"

#include <iostream>
#include <boost/asio.hpp>

#include "include/native_byte_order.hpp"
#include "include/flow_mgr.hpp"
#include "include/request.hpp"
#include "include/response.hpp"

#include "include/types.hpp"

using boost::asio::local::stream_protocol;

GREETD_CLIENT::GREETD_CLIENT()
{
    //m_request = new REQUEST( CREATE_SESSION );
    m_FlowMgr = new FLOW_MGR;
}

GREETD_CLIENT::~GREETD_CLIENT()
{
    if( m_socket )
        delete m_socket;
    delete m_FlowMgr;
}


bool GREETD_CLIENT::Connect()
{
    //std::cout << "In connect" << std::endl;
    const char* buf = std::getenv( "GREETD_SOCK" );
    //std::cout << buf << std::endl;
    boost::asio::io_context io_context;
    m_socket = new stream_protocol::socket( io_context );
    //if( m_socket )
    //    std::cout << buf << std::endl;
    try
    {
        //    std::cout << "try async connect" << std::endl;
        m_socket->connect( stream_protocol::endpoint( buf ) );
        //    std::cout << "async connect done" << std::endl;
    }
    catch( const std::exception& e )
    {
        std::cout << "Exception raised: " << e.what() << '\n';
        return false;
    }
    return true;
}


void GREETD_CLIENT::InitFlowMgr( const std::string& aUsername ) const
{
    m_FlowMgr->SetCreateSessionRequest( aUsername );
}


void GREETD_CLIENT::Cancel() const
{
    m_FlowMgr->CancelSession();
    UpdateFlow();
}


size_t GREETD_CLIENT::Write( const char* aBuffer, size_t aSizeBuffer )
{
    return boost::asio::write( *m_socket, boost::asio::buffer( aBuffer, aSizeBuffer ),
                               boost::asio::transfer_exactly( aSizeBuffer ) );
}


size_t GREETD_CLIENT::Read( char* aBuffer, size_t aSizeBuffer )
{
    return boost::asio::read( *m_socket, boost::asio::buffer( aBuffer, aSizeBuffer ),
                              boost::asio::transfer_exactly( aSizeBuffer ) );
}


void GREETD_CLIENT::SendRequestToServer()
{
    const REQUEST*    aRequest = m_FlowMgr->GetRequest();
    char              len_bytes[4];
    const std::string msg = aRequest->GetMsg();

    ToNativeByteOrder( msg.size(), len_bytes );

    Write( len_bytes, 4 );
    Write( msg.c_str(), msg.size() );
}


void GREETD_CLIENT::GetResponseFmServer()
{
    char reply_bytes[4];
    Read( reply_bytes, 4 );

    size_t reply_size = 0;
    FmNativeByteOrder( reply_bytes, &reply_size );

    char reply[reply_size + 1];
    reply[reply_size] = '\0';
    Read( reply, reply_size );

    const JsonValue json = boost::json::parse( reply );

    m_response = new RESPONSE( json );
    m_FlowMgr->SetResponse( m_response );
}


RESPONSE* GREETD_CLIENT::GetResponse() const
{
    return m_response;
}


void GREETD_CLIENT::SetPassword( const std::string& aPassword ) const
{
    m_FlowMgr->SetPassword( aPassword );
    UpdateFlow();
}


void GREETD_CLIENT::StartSession( const std::vector<std::string>& aCommand ) const
{
    m_FlowMgr->SetCommand( aCommand );
    UpdateFlow();
}


void GREETD_CLIENT::UpdateFlow() const
{
    m_FlowMgr->UpdateRequest();
}


void GREETD_CLIENT::CloseSocket()
{
    m_socket->close();
    delete m_socket;
    m_socket = nullptr;
}