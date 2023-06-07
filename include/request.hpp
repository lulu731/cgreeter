#ifndef _REQUEST_HPP_
#define _REQUEST_HPP_

#include <string>
#include <vector>

#include "include/types.hpp"

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
    MSG_TYPE                m_MsgType;
    JsonString              m_StringField;
    std::vector<JsonString> m_Cmd;
    std::vector<JsonString> m_Env;
    std::string             m_Msg;
    void                    SetMSG();
    void                    CreateSession( const JsonString* aUsername, JsonValue* aJsonRequest );
    void PostAuthMessageResponse( const JsonString* aResponse, JsonValue* aJsonRequest );
    void StartSession( const std::vector<JsonString>& aCmd, const std::vector<JsonString>& aEnv,
                       JsonValue* aJsonRequest );
    void CancelSession( JsonValue* aJsonRequest );

public:
    explicit REQUEST( MSG_TYPE aMsgType );
    REQUEST( MSG_TYPE aMsgType, const std::string& aStringField );
    REQUEST( MSG_TYPE aType, const std::vector<std::string> aField,
             const std::vector<std::string> aEnv );
    const std::string GetMsg() const;
};

#endif