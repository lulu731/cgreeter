#ifndef _FLOW_MGR_HPP_
#define _FLOW_MGR_HPP_

#include <string>

#include "include/request.hpp"
#include "include/response.hpp"

class FLOW_MGR
{
private:
    REQUEST*                 m_Request = nullptr;
    RESPONSE*                m_Response = nullptr;
    std::string              m_Password;
    bool                     m_PasswordSet = false;
    bool                     m_CancelSession = false;
    std::vector<std::string> m_Command;
    bool                     m_CommandSet = false;
    std::vector<std::string> m_Environment;
    bool                     m_EnvironmentSet = false;

public:
    ~FLOW_MGR();
    void      SetCreateSessionRequest( const std::string& aUsername );
    void      SetPassword( const std::string& aPassword );
    void      SetResponse( RESPONSE* aResponse );
    void      SetCommand( const std::vector<std::string>& aCommand );
    void      SetEnvironment( const std::vector<std::string>& aEnvironment );
    void      CancelSession();
    void      UpdateRequest();
    REQUEST*  GetRequest() const;
    RESPONSE* GetResponse() const;
};

#endif // _FLOW_MGR_HPP_