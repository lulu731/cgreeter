#ifndef _FLOW_MGR_HPP_
#define _FLOW_MGR_HPP_

#include <string>
#include <vector>
#include <exception>

#include "include/request.hpp"
#include "include/response.hpp"

const int         MAX_SEND_PASSWD_ATTEMPTS = 3;
const std::string WRONG_PASSWD = "Wrong password";

class FLOW_MGR
{
private:
    REQUEST*                 m_Request = nullptr;
    RESPONSE*                m_Response = nullptr;
    int                      m_SendPasswdAttempt = 0;
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

class FLOW_MGR_EXCEPTION : public std::exception
{
private:
    std::string m_What;

public:
    FLOW_MGR_EXCEPTION( const std::string& aWhat );
};

#endif // _FLOW_MGR_HPP_