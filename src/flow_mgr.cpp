#include "include/flow_mgr.hpp"

FLOW_MGR::~FLOW_MGR()
{
    if( m_Request )
        delete m_Request;

    if( m_Response )
    {
        delete m_Response;
    }
}


void FLOW_MGR::SetCreateSessionRequest( const std::string& aUsername )
{
    m_Request = new REQUEST( CREATE_SESSION, aUsername );
}


void FLOW_MGR::SetPassword( const std::string& aPassword )
{
    m_Password = aPassword;
}


void FLOW_MGR::SetResponse( RESPONSE* aResponse )
{
    m_Response = aResponse;
}


void FLOW_MGR::CancelSession()
{
    m_CancelSession = true;
}

void FLOW_MGR::UpdateRequest()
{
    delete m_Request;
    m_Request = nullptr;
    switch( m_Response->GetType() )
    {
    case AUTH_MESSAGE:
        if( !m_CancelSession )
        {
            m_Request = new REQUEST( POST_AUTH_MESSAGE_RESPONSE, m_Password );
        }
        else
        {
            m_Request = new REQUEST( CANCEL_SESSION );
        }
        break;

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