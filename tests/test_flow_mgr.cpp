#define BOOST_TEST_MODULE test FLOW_MGR class

#include "include/flow_mgr.hpp"

#include <boost/test/included/unit_test.hpp>
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

    // Receive succes response
    RESPONSE* successResponse = GetResponseFmServer( JsonSuccessResponse );
    FlowMgr.SetResponse( successResponse );
    FlowMgr.UpdateRequest();

    REQUEST* SuccessRequest = FlowMgr.GetRequest();

    BOOST_CHECK( !SuccessRequest );
}

BOOST_FIXTURE_TEST_CASE( TestCreateSessionToCancel, test_flow_mgr )
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