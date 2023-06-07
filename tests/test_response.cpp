#define BOOST_TEST_MODULE test response class

#include "include/response.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/json/src.hpp>

#include "include/types.hpp"

BOOST_AUTO_TEST_CASE( TestSuccessResponseCreator )
{
    const char*     ResponseSuccess = "{\"type\": \"success\"}";
    const JsonValue JsonResp = boost::json::parse( ResponseSuccess );

    RESPONSE Response( JsonResp );

    BOOST_CHECK( Response.IsSuccess() && !Response.IsError() && !Response.IsAuthMessage() );
}


BOOST_AUTO_TEST_CASE( TestErrorResponseCreator )
{
    const char*     ResponseError = "{\"type\": \"error\",\
    \"error_type\": \"auth_error\", \"description\": \"invalid_request\"}";
    const JsonValue JsonResp = boost::json::parse( ResponseError );
    RESPONSE        Response( JsonResp );
    BOOST_CHECK( !Response.IsSuccess() && Response.IsError() && !Response.IsAuthMessage() );
}


BOOST_AUTO_TEST_CASE( TestAuthMessageResponseCreator )
{
    const char*     ResponseAuthMessage = "{\"type\": \"auth_message\",\
    \"auth_message_type\": \"secret\", \"auth_message\": \"Valid auth_message\"}";
    const JsonValue JsonResp = boost::json::parse( ResponseAuthMessage );
    RESPONSE        Response( JsonResp );
    BOOST_CHECK( !Response.IsSuccess() && !Response.IsError() && Response.IsAuthMessage() );
}