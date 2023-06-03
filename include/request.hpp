#ifndef _REQUEST_HPP_
#define _REQUEST_HPP_

#include <string>
#include <boost/json.hpp>
#include <vector>

using namespace boost::json;

enum MSG_TYPE
{
    CREATE_SESSION,
    POST_AUTH_MESSAGE_RESPONSE,
    START_SESSION,
    CANCEL_SESSION
};

class REQUEST
{
private:
    MSG_TYPE m_MsgType;
    string m_StringField;
    std::vector<string> m_Cmd;
    std::vector<string> m_Env;
    void CreateSession( const string &aUsername, value &aJsonRequest);
    void PostAuthMessageResponse( const string &aResponse, value &aJsonRequest );
    void StartSession( const std::vector<string> &aCmd,
        const std::vector<string> &aEnv,
        value &aJsonRequest );
    void CancelSession( value &aJsonRequest );

public:
    REQUEST(MSG_TYPE aMsgType);
    REQUEST( MSG_TYPE aMsgType, const std::string &aStringField);
    REQUEST(MSG_TYPE aType, const std::vector<std::string> aField, const std::vector<std::string> aEnv );
    const std::string GetMsg();
};

#endif