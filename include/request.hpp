#ifndef _REQUEST_HPP_
#define _REQUEST_HPP_

#include <string>
#include <boost/json.hpp>
#include <vector>

using namespace boost::json;

class REQUEST
{
public:
    static void CreateSession( const string &aUsername, value &aJsonRequest);
    static void PostAuthMessageResponse( const string &aResponse, value &aJsonRequest );
    static void StartSession( const std::vector<string> &aCmd,
        const std::vector<string> &aEnv,
        value &aJsonRequest );
    static void CancelSession( value &aJsonRequest );
    virtual value* GetJsonRequest() = 0;
};

#endif