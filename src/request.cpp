#include "request.hpp"

 void REQUEST::CreateSession( const string &aUsername, object &aJsonRequest ) {
    aJsonRequest["type"] = "create_session";
    aJsonRequest["username"] = aUsername;
}


void REQUEST::PostAuthMessageResponse( const string &aResponse, object &aJsonRequest ) {
    aJsonRequest["type"] = "post_auth_message_response";
    aJsonRequest["response"] = aResponse;
}


void REQUEST::StartSession( const std::vector<string> &aCmd,
        const std::vector<string> &aEnv,
        object &aJsonRequest ) {
    aJsonRequest["type"] = "start_session";
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

    aJsonRequest["cmd"] = cmdArray;
    aJsonRequest["env"] = envArray;
}


void REQUEST::CancelSession( object &aJsonRequest ) {
    aJsonRequest["type"] = "cancel_session";
}