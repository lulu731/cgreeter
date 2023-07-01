#define BOOST_TEST_MODULE test FLOW_MGR class

#include "include/flow_mgr.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/json/src.hpp>
#include "include/request.hpp"
#include "include/response.hpp"
#include "include/types.hpp"

struct test_flow_mgr
{
    FLOW_MGR FlowMgr;

    test_flow_mgr() {}

    ~test_flow_mgr() {}
    void setup()
    {
        // Client gets UserName, then FlowMgr creates CreateSession request
        FlowMgr.SetCreateSessionRequest( "test" );
    }
};


const JsonValue jsonAuthMessageResponse = { { "type", "auth_message" },
                                            { "auth_message_type", "visible" },
                                            { "auth_message", "password: " } };

const JsonValue JsonSuccessResponse = { { "type", "success" } };

const std::string aWrongPasswordResponse = "Wrong password";

const JsonValue JsonAuthErrorResponse = { { "type", "error" },
                                          { "error_type", "auth_error" },
                                          { "description", aWrongPasswordResponse } };

const std::string aErrorResponse = "There was an error";

const JsonValue JsonErrorResponse = { { "type", "error" },
                                      { "error_type", "error" },
                                      { "description", aErrorResponse } };

RESPONSE* GetResponseFmServer( const JsonValue& aJsonResponse )
{
    RESPONSE* response = new RESPONSE( aJsonResponse );
    return response;
}


JsonObject GetRequestMessageAsObject( const REQUEST* aRequest )
{
    const std::string message = aRequest->GetMsg();
    return boost::json::value_to<JsonObject>( parse( JsonString( message ) ) );
}


BOOST_FIXTURE_TEST_CASE( TestInitiateFlowMgr, test_flow_mgr )
{
    JsonObject aObjMessage = GetRequestMessageAsObject( FlowMgr.GetRequest() );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["type"] ), "create_session" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["username"] ), "test" );
}


BOOST_FIXTURE_TEST_CASE( TestCreateSessionToSuccess, test_flow_mgr )
{
    // CreateSession request has been sent, AuthMessage response is received from server
    // Response object is created
    RESPONSE* response = GetResponseFmServer( jsonAuthMessageResponse );

    FlowMgr.SetResponse( response );
    BOOST_CHECK( FlowMgr.GetResponse()->IsAuthMessage() );

    // User writes his password
    std::string Password = "aPassword";
    FlowMgr.SetPassword( Password );
    FlowMgr.UpdateRequest();

    // Send password to server
    REQUEST* request = FlowMgr.GetRequest();

    JsonObject aObjMessage = GetRequestMessageAsObject( request );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["type"] ),
                       "post_auth_message_response" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["response"] ), Password );

    // Receive success response, ready to start session
    response = GetResponseFmServer( JsonSuccessResponse );
    FlowMgr.SetResponse( response );

    const std::vector<std::string> Command = { "start --session" };
    FlowMgr.SetCommand( Command );
    const std::vector<std::string> Env = { "envVariable" };
    FlowMgr.SetEnvironment( Env );
    FlowMgr.UpdateRequest();

    request = FlowMgr.GetRequest();

    aObjMessage = GetRequestMessageAsObject( request );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["type"] ), "start_session" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjMessage["cmd"] ).at( 0 ),
                       JsonString( Command[0] ) );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonArray>( aObjMessage["env"] ).at( 0 ),
                       JsonString( Env[0] ) );

    // Receive success response, session is started
    response = GetResponseFmServer( JsonSuccessResponse );
    FlowMgr.SetResponse( response );
    FlowMgr.UpdateRequest();

    request = FlowMgr.GetRequest();

    BOOST_CHECK( !request );
}


BOOST_FIXTURE_TEST_CASE( TestCancelCreateSession, test_flow_mgr )
{
    // Then send jsonRequest to the server, and then build a response
    RESPONSE* response = GetResponseFmServer( jsonAuthMessageResponse );

    FlowMgr.SetResponse( response );
    BOOST_CHECK( FlowMgr.GetResponse()->IsAuthMessage() );

    // User cancels session creation
    FlowMgr.CancelSession();
    FlowMgr.UpdateRequest();

    REQUEST* request = FlowMgr.GetRequest();

    JsonObject aObjMessage = GetRequestMessageAsObject( request );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjMessage["type"] ), "cancel_session" );

    RESPONSE* successResponse = GetResponseFmServer( JsonSuccessResponse );
    FlowMgr.SetResponse( successResponse );
    FlowMgr.UpdateRequest();

    REQUEST* SuccessRequest = FlowMgr.GetRequest();

    BOOST_CHECK( !SuccessRequest );
}


std::vector<int> AttemptSet = { 0, 1, 2, 3, 4 };

BOOST_DATA_TEST_CASE_F( test_flow_mgr, TestCreateSessionWrongPassword, AttemptSet )
{
    // CreateSession request has been sent, AuthMessage response is received from server
    // Response object is created
    RESPONSE* response = GetResponseFmServer( jsonAuthMessageResponse );

    FlowMgr.SetResponse( response );

    // User writes his password
    const std::string Password = "aPassword";

    for( int Attempt = 0; Attempt < sample; Attempt++ )
    {
        FlowMgr.SetPassword( Password );
        FlowMgr.UpdateRequest();

        // Send password to server
        //REQUEST* request = FlowMgr.GetRequest();

        // Receive bad password error response
        response = GetResponseFmServer( JsonAuthErrorResponse );
        if( Attempt >= MAX_SEND_PASSWD_ATTEMPTS - 1 )
        {
            BOOST_CHECK_THROW( FlowMgr.SetResponse( response ), FLOW_MGR_EXCEPTION );
        }
        else
            FlowMgr.SetResponse( response );
    }
}


BOOST_FIXTURE_TEST_CASE( TestErrorResponse, test_flow_mgr )
{
    // Then send jsonRequest to the server, and then build a response
    RESPONSE* response = GetResponseFmServer( jsonAuthMessageResponse );

    FlowMgr.SetResponse( response );

    // User enters password
    const std::string Password = "aPassword";

    FlowMgr.SetPassword( Password );
    FlowMgr.UpdateRequest();

    RESPONSE* errorResponse = GetResponseFmServer( JsonErrorResponse );

    BOOST_CHECK_THROW( FlowMgr.SetResponse( errorResponse ), FLOW_MGR_EXCEPTION );
}