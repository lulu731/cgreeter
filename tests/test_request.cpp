#define BOOST_TEST_MODULE test request class

#include "include/request.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/json/src.hpp>

#include "include/types.hpp"

BOOST_AUTO_TEST_CASE( CreateSessionRequest )
{
    const MSG_TYPE    mt = CREATE_SESSION;
    const std::string aUsername = "test";
    REQUEST           req( mt, aUsername );

    const std::string message = req.GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( parse( JsonString( message ) ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ), "create_session" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["username"] ), aUsername );
}

BOOST_AUTO_TEST_CASE( PostAuthMessageResponseRequest )
{
    const MSG_TYPE    mt = POST_AUTH_MESSAGE_RESPONSE;
    const std::string aResponse = "test";
    REQUEST           req( mt, aResponse );

    const std::string message = req.GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( boost::json::parse( message ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ),
                       "post_auth_message_response" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["response"] ), aResponse );
}

BOOST_AUTO_TEST_CASE( StartSessionRequest )
{
    const MSG_TYPE                 mt = START_SESSION;
    const std::vector<std::string> aCmd = { "test", "test2" };
    const std::vector<std::string> aEnv = { "test", "test2", "test3" };
    REQUEST                        req( mt, aCmd, aEnv );

    const std::string message = req.GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( boost::json::parse( message ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ), "start_session" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjReq["cmd"] ).at( 0 ),
                       JsonString( aCmd[0] ) );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjReq["env"] ).at( 0 ),
                       JsonString( aEnv[0] ) );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjReq["cmd"] ).size(), aCmd.size() );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjReq["env"] ).size(), aEnv.size() );
}

BOOST_AUTO_TEST_CASE( CancelSessionRequest )
{
    const MSG_TYPE mt = CANCEL_SESSION;
    REQUEST        req( mt );

    const std::string message = req.GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( boost::json::parse( message ) );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ), "cancel_session" );
}