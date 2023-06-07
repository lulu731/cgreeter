#include "include/response.hpp"

#include <boost/json.hpp>

#include "include/types.hpp"

RESPONSE::RESPONSE( const JsonValue& aJsonResponse ) : m_JsonResponse( aJsonResponse )
{
    JsonString type = boost::json::value_to<JsonString>(
            boost::json::value_to<JsonObject>( m_JsonResponse )["type"] );
    if( type == "success" )
    {
        m_Type = SUCCESS;
    }
    else if( type == "error" )
    {
        m_Type = ERROR;
    }
    else if( type == "auth_message" )
    {
        m_Type = AUTH_MESSAGE;
    }
}


bool RESPONSE::IsSuccess()
{
    return m_Type == SUCCESS;
}


bool RESPONSE::IsError()
{
    return m_Type == ERROR;
}


bool RESPONSE::IsAuthMessage()
{
    return m_Type == AUTH_MESSAGE;
}