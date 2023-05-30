#ifndef _REQUEST_HPP_
#define _REQUEST_HPP_

#include <string>
#include <boost/json.hpp>
#include <vector>

using namespace boost::json;

class REQUEST
{
public:
    static void CreateSession( const string &aUsername, object &aJsonRequest);
    static void PostAuthMessageResponse( const string &aResponse, object &aJsonRequest );
    static void StartSession( const std::vector<string> &aCmd,
        const std::vector<string> &aEnv,
        object &aJsonRequest );
    static void CancelSession( object &aJsonRequest );
};

#endif