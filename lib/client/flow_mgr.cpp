#include "include/flow_mgr.hpp"

FLOW_MGR::~FLOW_MGR()
{
    if( m_Request )
        delete m_Request;

    if( m_Response )
        delete m_Response;
}


void FLOW_MGR::SetCreateSessionRequest( const std::string& aUsername )
{
    m_Request = new REQUEST( CREATE_SESSION, aUsername );
}


void FLOW_MGR::SetPassword( const std::string& aPassword )
{
    m_Password = aPassword;
    m_PasswordSet = true;
}


void FLOW_MGR::SetResponse( RESPONSE* aResponse )
{
    if( m_Response )
        delete m_Response;
    m_Response = aResponse;
}


void FLOW_MGR::CancelSession()
{
    m_CancelSession = true;
}


void FLOW_MGR::SetCommand( const std::vector<std::string>& aCommand )
{
    m_Command = aCommand;
    m_CommandSet = true;
}


void FLOW_MGR::SetEnvironment( const std::vector<std::string>& aEnvironment )
{
    m_Environment = aEnvironment;
    m_EnvironmentSet = true;
}


void FLOW_MGR::UpdateRequest()
{
    if( m_Request )
        delete m_Request;
    m_Request = nullptr;

    switch( m_Response->GetType() )
    {
    case ERROR:
        m_Request = new REQUEST( CANCEL_SESSION );
        break;
    case AUTH_MESSAGE:
        if( !m_CancelSession && m_PasswordSet )
        {
            m_Request = new REQUEST( POST_AUTH_MESSAGE_RESPONSE, m_Password );
            m_PasswordSet = false;
        }
        else
        {
            m_Request = new REQUEST( CANCEL_SESSION );
        }
        break;
    case SUCCESS:
        if( m_CommandSet || m_EnvironmentSet )
        {
            m_Request = new REQUEST( START_SESSION, m_Command, m_Environment );
            m_CommandSet = false;
            m_EnvironmentSet = false;
        }
    default: break;
    }
}


REQUEST* FLOW_MGR::GetRequest() const
{
    return m_Request;
}


RESPONSE* FLOW_MGR::GetResponse() const
{
    return m_Response;
}


FLOW_MGR_EXCEPTION::FLOW_MGR_EXCEPTION( const std::string& aWhat ) : m_What( aWhat )
{
}