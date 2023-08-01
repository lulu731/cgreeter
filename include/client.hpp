#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "include/flow_mgr.hpp"
#include "include/request.hpp"
#include "include/response.hpp"

using boost::asio::local::stream_protocol;

class GREETD_CLIENT
{
private:
    FLOW_MGR* m_FlowMgr;
    REQUEST*  m_request;
    RESPONSE* m_response;

    stream_protocol::socket* m_socket;
    size_t                   Write( const char* aBuffer, size_t aSizeBuffer );
    size_t                   Read( char* aBuffer, size_t aSizeBuffer );


public:
    GREETD_CLIENT();
    ~GREETD_CLIENT();
    bool      Connect();
    void      InitFlowMgr( const std::string& aUsername ) const;
    void      SendRequestToServer();
    void      GetResponseFmServer();
    RESPONSE* GetResponse() const;
    void      SetPassword( const std::string& aPassword ) const;
    void      Cancel() const;
    void      StartSession( const std::vector<std::string>& aCommand ) const;
    void      UpdateFlow() const;
    void      CloseSocket();
};


#endif // _CLIENT_HPP
