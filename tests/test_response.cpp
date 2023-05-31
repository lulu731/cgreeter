#include "response.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestNextReqForSuccess  )
{
    const char *ResponseSuccess = "{\"type\": \"success\"}";
    const value JsonResp = boost::json::parse( ResponseSuccess );

    RESPONSE_SUCCESS Response( JsonResp );

    REQUEST *Req;
    Req = Response.CreateNextRequest();
    value *JsonReq;
    JsonReq = Req->GetJsonRequest();

    BOOST_CHECK( JsonReq == nullptr );

    delete Req;
}