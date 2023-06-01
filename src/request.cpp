#include "request.hpp"

 void REQUEST::CreateSession( const string &aUsername, value &aJsonRequest ) {
    aJsonRequest = { {"type", "create_session" },
                { "username", aUsername } };
}


void REQUEST::PostAuthMessageResponse( const string &aResponse, value &aJsonRequest ) {
    aJsonRequest  = { { "type", "post_auth_message_response" },
    { "response", aResponse } };
}


void REQUEST::StartSession( const std::vector<string> &aCmd,
        const std::vector<string> &aEnv,
        value &aJsonRequest ) {

    array cmdArray;
    for (size_t i = 0; i < aCmd.size(); i++)
    {
        cmdArray.emplace_back( aCmd[i] );
    }

    array envArray;
    for (size_t i = 0; i < aEnv.size(); i++)
    {
        envArray.emplace_back( aEnv[i] );
    }

    aJsonRequest = { {"type", "start_session"},
        { "cmd", cmdArray },
        { "env", envArray} };
}


void REQUEST::CancelSession( value &aJsonRequest ) {
    aJsonRequest = { {"type", "cancel_session"} };
}