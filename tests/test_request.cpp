#define BOOST_TEST_MODULE test request class

#include "request.hpp"
#include <boost/test/included/unit_test.hpp>
#include <boost/json/src.hpp>

BOOST_AUTO_TEST_CASE( CreateSessionRequest )
{
    const string aUsername = "test";
    value aJsonRequest;
    REQUEST::CreateSession( aUsername, aJsonRequest );

    object aObjeReq = value_to<object>( aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aObjeReq["type"] ), "create_session" );
    BOOST_CHECK_EQUAL( value_to<string>( aObjeReq["username"] ), aUsername );
}

BOOST_AUTO_TEST_CASE( PostAuthMessageResponseRequest )
{
    const string aResponse = "test";
    value aJsonRequest;
    REQUEST::PostAuthMessageResponse( aResponse, aJsonRequest );
    object aObjReq = value_to<object>( aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aObjReq["type"] ), "post_auth_message_response" );
    BOOST_CHECK_EQUAL( value_to<string>( aObjReq["response"] ), aResponse );
}

BOOST_AUTO_TEST_CASE( StartSessionRequest )
{
    const std::vector<string> aCmd = { "test", "test2" };
    const std::vector<string> aEnv = { "test", "test2", "test3" };
    value aJsonRequest;
    REQUEST::StartSession( aCmd, aEnv, aJsonRequest );
    object aObjReq = value_to<object>( aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aObjReq["type"] ), "start_session" );
    BOOST_CHECK_EQUAL( value_to<array>( aObjReq["cmd"] ).at(0), aCmd.at(0) );
    BOOST_CHECK_EQUAL( value_to<array>( aObjReq["env"] ).at(0), aEnv.at(0) );
    BOOST_CHECK_EQUAL( value_to<array>( aObjReq["cmd"] ).size(), aCmd.size() );
    BOOST_CHECK_EQUAL( value_to<array>( aObjReq["env"] ).size(), aEnv.size() );
}

BOOST_AUTO_TEST_CASE( CancelSessionRequest )
{
    value aJsonRequest;
    REQUEST::CancelSession( aJsonRequest );
    object aObjReq = value_to<object>( aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aObjReq["type"] ), "cancel_session" );
}