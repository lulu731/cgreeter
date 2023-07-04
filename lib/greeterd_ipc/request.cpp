#include "include/request.hpp"

#include <string>

#include "include/types.hpp"

REQUEST::REQUEST( MSG_TYPE aMsgType ) : m_MsgType( aMsgType )
{
    SetMSG();
}
REQUEST::REQUEST( MSG_TYPE aMsgType, const std::string& aUserName ) :
        m_MsgType( aMsgType ), m_StringField( aUserName )
{
    SetMSG();
}


REQUEST::REQUEST( MSG_TYPE aType, const std::vector<std::string> aField,
                  const std::vector<std::string> aEnv ) :
        m_MsgType( aType )
{
    for( size_t i = 0; i < aField.size(); i++ )
        m_Cmd.push_back( JsonString( aField[i] ) );

    for( size_t i = 0; i < aEnv.size(); i++ )
        m_Env.push_back( JsonString( aEnv[i] ) );
    SetMSG();
}

void REQUEST::SetMSG()
{
    JsonValue jsonRequest;
    switch( m_MsgType )
    {
    case CREATE_SESSION:
    {
        CreateSession( &m_StringField, &jsonRequest );
        break;
    }

    case POST_AUTH_MESSAGE_RESPONSE:
    {
        PostAuthMessageResponse( &m_StringField, &jsonRequest );
        break;
    }

    case START_SESSION:
    {
        StartSession( m_Cmd, m_Env, &jsonRequest );
        break;
    }

    case CANCEL_SESSION:
    {
        CancelSession( &jsonRequest );
        break;
    }

    default: break;
    };

    m_Msg = serialize( jsonRequest );
}

const std::string REQUEST::GetMsg() const
{
    return m_Msg;
}


void REQUEST::CreateSession( const JsonString* aUsername, JsonValue* aJsonRequest )
{
    *aJsonRequest = { { "type", "create_session" }, { "username", *aUsername } };
}


void REQUEST::PostAuthMessageResponse( const JsonString* aResponse, JsonValue* aJsonRequest )
{
    *aJsonRequest = { { "type", "post_auth_message_response" }, { "response", *aResponse } };
}


void REQUEST::StartSession( const std::vector<JsonString>& aCmd,
                            const std::vector<JsonString>& aEnv, JsonValue* aJsonRequest )
{
    JsonArray cmdArray;
    for( size_t i = 0; i < aCmd.size(); i++ )
    {
        cmdArray.emplace_back( aCmd[i] );
    }

    JsonArray envArray;
    for( size_t i = 0; i < aEnv.size(); i++ )
    {
        envArray.emplace_back( aEnv[i] );
    }

    *aJsonRequest = { { "type", "start_session" }, { "cmd", cmdArray }, { "env", envArray } };
}


void REQUEST::CancelSession( JsonValue* aJsonRequest )
{
    *aJsonRequest = { { "type", "cancel_session" } };
}