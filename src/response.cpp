#include "include/response.hpp"

#include <boost/json.hpp>

#include "include/types.hpp"

RESPONSE::RESPONSE( const JsonValue& aJsonResponse )
{
    JsonString type = boost::json::value_to<JsonString>(
            boost::json::value_to<JsonObject>( aJsonResponse )["type"] );
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


RESPONSE_TYPE RESPONSE::GetType() const
{
    return m_Type;
}


bool RESPONSE::IsSuccess() const
{
    return m_Type == SUCCESS;
}


bool RESPONSE::IsError() const
{
    return m_Type == ERROR;
}


bool RESPONSE::IsAuthMessage() const
{
    return m_Type == AUTH_MESSAGE;
}