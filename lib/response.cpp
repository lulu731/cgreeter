#include "include/response.hpp"

#include <boost/json.hpp>

#include "include/types.hpp"

RESPONSE::RESPONSE( const JsonValue& aJsonResponse ) : m_JsonResponse( aJsonResponse )
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
        InitFieldData( "error_type", "description" );
    }
    else if( type == "auth_message" )
    {
        m_Type = AUTH_MESSAGE;
        InitFieldData( "auth_message_type", "auth_message" );
    }
}

void RESPONSE::InitFieldData( const std::string& aTypeKey, const std::string& aDescriptionKey )
{
    m_FieldType = boost::json::value_to<JsonString>(
            boost::json::value_to<JsonObject>( m_JsonResponse )[aTypeKey] );
    m_FieldDescription = boost::json::value_to<JsonString>(
            boost::json::value_to<JsonObject>( m_JsonResponse )[aDescriptionKey] );
}
/*JsonValue RESPONSE::GetJsonResponse() const {
    return m_JsonResponse;
}*/


RESPONSE_TYPE RESPONSE::GetType() const
{
    return m_Type;
}


std::string RESPONSE::GetFieldType() const
{
    return m_FieldType;
}


std::string RESPONSE::GetFieldDescription() const
{
    return m_FieldDescription;
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