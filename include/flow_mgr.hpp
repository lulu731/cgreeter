#ifndef _FLOW_MGR_HPP_
#define _FLOW_MGR_HPP_

#include <string>

#include "include/request.hpp"
#include "include/response.hpp"

class FLOW_MGR
{
private:
    REQUEST*    m_Request = nullptr;
    RESPONSE*   m_Response = nullptr;
    std::string m_Password;

public:
    FLOW_MGR( /* args */ );
    ~FLOW_MGR();
    void      SetCreateSessionRequest( const std::string& aUsername );
    void      SetPassword( const std::string& aPassword );
    void      SetResponse( RESPONSE* aResponse );
    void      UpdateRequest();
    REQUEST*  GetRequest() const;
    RESPONSE* GetResponse() const;
};

#endif // _FLOW_MGR_HPP_