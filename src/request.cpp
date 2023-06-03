#include "request.hpp"

REQUEST::REQUEST( MSG_TYPE aMsgType ) : m_MsgType( aMsgType )
{
}
REQUEST::REQUEST( MSG_TYPE aMsgType, const std::string& aUserName ) :
        m_MsgType( aMsgType ), m_StringField( aUserName ){};


REQUEST::REQUEST( MSG_TYPE aType, const std::vector<std::string> aField,
                  const std::vector<std::string> aEnv ) :
        m_MsgType( aType )
{
    for( size_t i = 0; i < aField.size(); i++ )
        m_Cmd.push_back( string( aField[i] ) );

    for( size_t i = 0; i < aEnv.size(); i++ )
        m_Env.push_back( string( aEnv[i] ) );
};


const std::string REQUEST::GetMsg()
{
    value jsonRequest;
    switch( m_MsgType )
    {
    case CREATE_SESSION:
    {
        CreateSession( m_StringField, jsonRequest );
        break;
    }

    case POST_AUTH_MESSAGE_RESPONSE:
    {
        PostAuthMessageResponse( m_StringField, jsonRequest );
        break;
    }

    case START_SESSION:
    {
        StartSession( m_Cmd, m_Env, jsonRequest );
        break;
    }

    case CANCEL_SESSION:
    {
        CancelSession( jsonRequest );
        break;
    }

    default: break;
    };
    return serialize( jsonRequest );
}


void REQUEST::CreateSession( const string& aUsername, value& aJsonRequest )
{
    aJsonRequest = { { "type", "create_session" }, { "username", aUsername } };
}


void REQUEST::PostAuthMessageResponse( const string& aResponse, value& aJsonRequest )
{
    aJsonRequest = { { "type", "post_auth_message_response" }, { "response", aResponse } };
}


void REQUEST::StartSession( const std::vector<string>& aCmd, const std::vector<string>& aEnv,
                            value& aJsonRequest )
{
    array cmdArray;
    for( size_t i = 0; i < aCmd.size(); i++ )
    {
        cmdArray.emplace_back( aCmd[i] );
    }

    array envArray;
    for( size_t i = 0; i < aEnv.size(); i++ )
    {
        envArray.emplace_back( aEnv[i] );
    }

    aJsonRequest = { { "type", "start_session" }, { "cmd", cmdArray }, { "env", envArray } };
}


void REQUEST::CancelSession( value& aJsonRequest )
{
    aJsonRequest = { { "type", "cancel_session" } };
}