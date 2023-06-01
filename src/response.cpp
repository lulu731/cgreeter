#include "response.hpp"

RESPONSE::RESPONSE( const value &aJsonResponse ) : m_JsonResponse( aJsonResponse )
{
    string type = value_to<string>( value_to<object>( m_JsonResponse )["type"] );
    if ( type == "success" )
    {
        m_Type = SUCCESS;
    }
    else if ( type == "error" )
    {
        m_Type = ERROR;
    }
    else if ( type == "auth_message" )
    {
        m_Type = AUTH_MESSAGE;
    }
}


bool RESPONSE::IsSuccess() {
    return m_Type == SUCCESS;
}


bool RESPONSE::IsError() {
    return m_Type == ERROR;
}


bool RESPONSE::IsAuthMessage() {
    return m_Type == AUTH_MESSAGE;
}