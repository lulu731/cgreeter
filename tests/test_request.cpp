#include "request.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/json/src.hpp>

BOOST_AUTO_TEST_CASE( CreateSession )
{
    const string aUsername = "test";
    object aJsonRequest;
    REQUEST::CreateSession( aUsername, aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["type"] ), "create_session" );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["username"] ), aUsername );
}

BOOST_AUTO_TEST_CASE( PostAuthMessageResponse )
{
    const string aResponse = "test";
    object aJsonRequest;
    REQUEST::PostAuthMessageResponse( aResponse, aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["type"] ), "post_auth_message_response" );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["response"] ), aResponse );
}

BOOST_AUTO_TEST_CASE( StartSession )
{
    const std::vector<string> aCmd = { "test", "test2" };
    const std::vector<string> aEnv = { "test", "test2", "test3" };
    object aJsonRequest;
    REQUEST::StartSession( aCmd, aEnv, aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["type"] ), "start_session" );
    BOOST_CHECK_EQUAL( value_to<array>( aJsonRequest["cmd"] ).at(0), aCmd.at(0) );
    BOOST_CHECK_EQUAL( value_to<array>( aJsonRequest["env"] ).at(0), aEnv.at(0) );
    BOOST_CHECK_EQUAL( value_to<array>( aJsonRequest["cmd"] ).size(), aCmd.size() );
    BOOST_CHECK_EQUAL( value_to<array>( aJsonRequest["env"] ).size(), aEnv.size() );
}

BOOST_AUTO_TEST_CASE( CancelSession )
{
    object aJsonRequest;
    REQUEST::CancelSession( aJsonRequest );
    BOOST_CHECK_EQUAL( value_to<string>( aJsonRequest["type"] ), "cancel_session" );
}