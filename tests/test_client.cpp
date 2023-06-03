#include "request.hpp"
#include "response.hpp"
#include <boost/test/unit_test.hpp>

void CreateSession( const string& aUsername, value& aJsonRequest )
{
    value jsonRequest;
    REQUEST::CreateSession( "test", jsonRequest );

    // Then send jsonRequest to the server, and then build a response
    value jsonResponse = { { "type", "auth_message" },
                           { "auth_message_type", "visible" },
                           { "auth_message", "password: " } };

    RESPONSE response( jsonResponse );
}

BOOST_AUTO_TEST_CASE( TestCreateSessionToSuccess )
{
    value jsonRequest;
    REQUEST::CreateSession( "test", jsonRequest );

    // Then send jsonRequest to the server, and then build a response
    value jsonResponse = { { "type", "auth_message" },
                           { "auth_message_type", "visible" },
                           { "auth_message", "password: " } };

    RESPONSE response( jsonResponse );

    BOOST_CHECK( response.IsAuthMessage() );

    // User writes his password
    value passwordRequest;
    REQUEST::PostAuthMessageResponse( "aPassword", passwordRequest );
    // Send password to server
    value    successJsonResponse = { { "type", "success" } };
    RESPONSE successResponse( successJsonResponse );

    BOOST_CHECK( successResponse.IsSuccess() );
}