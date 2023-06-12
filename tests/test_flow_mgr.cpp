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
        // Client gets UserName, then create request
        FlowMgr.SetCreateSessionRequest( "test" );
    }
};


BOOST_FIXTURE_TEST_CASE( TestInitiateFlowMgr, test_flow_mgr )
{
    const std::string message = FlowMgr.GetRequest()->GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( parse( JsonString( message ) ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ), "create_session" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["username"] ), "test" );
}

BOOST_FIXTURE_TEST_CASE( TestCreateSessionToSuccess, test_flow_mgr )
{
    // Then send jsonRequest to the server, and then build a response
    JsonValue jsonResponse = { { "type", "auth_message" },
                               { "auth_message_type", "visible" },
                               { "auth_message", "password: " } };
    RESPONSE* response = new RESPONSE( jsonResponse );
    BOOST_CHECK( response->IsAuthMessage() );

    FlowMgr.SetResponse( response );
    BOOST_CHECK( FlowMgr.GetResponse()->IsAuthMessage() );

    FlowMgr.UpdateRequest();
    // User writes his password
    std::string Password = "aPassword";
    FlowMgr.SetPassword( Password );
    FlowMgr.UpdateRequest();

    REQUEST* request = FlowMgr.GetRequest();
    // Send password to server

    const std::string message = request->GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( parse( JsonString( message ) ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ),
                       "post_auth_message_response" );
    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["response"] ), Password );

    JsonValue successJsonResponse = { { "type", "success" } };
    RESPONSE* successResponse = new RESPONSE( successJsonResponse );
    FlowMgr.SetResponse( successResponse );
    FlowMgr.UpdateRequest();

    REQUEST* SuccessRequest = FlowMgr.GetRequest();

    BOOST_CHECK( !SuccessRequest );
}

BOOST_FIXTURE_TEST_CASE( TestCreateSessionToCancel, test_flow_mgr )
{
    // Then send jsonRequest to the server, and then build a response
    JsonValue jsonResponse = { { "type", "auth_message" },
                               { "auth_message_type", "visible" },
                               { "auth_message", "password: " } };
    RESPONSE* response = new RESPONSE( jsonResponse );
    BOOST_CHECK( response->IsAuthMessage() );

    FlowMgr.SetResponse( response );
    BOOST_CHECK( FlowMgr.GetResponse()->IsAuthMessage() );

    // User cancels session
    FlowMgr.CancelSession();
    FlowMgr.UpdateRequest();

    REQUEST* request = FlowMgr.GetRequest();

    const std::string message = request->GetMsg();
    JsonObject        aObjReq = boost::json::value_to<JsonObject>( parse( JsonString( message ) ) );

    BOOST_CHECK_EQUAL( boost::json::value_to<JsonString>( aObjReq["type"] ), "cancel_session" );

    JsonValue successJsonResponse = { { "type", "success" } };
    RESPONSE* successResponse = new RESPONSE( successJsonResponse );
    FlowMgr.SetResponse( successResponse );
    FlowMgr.UpdateRequest();

    REQUEST* SuccessRequest = FlowMgr.GetRequest();

    BOOST_CHECK( !SuccessRequest );
}