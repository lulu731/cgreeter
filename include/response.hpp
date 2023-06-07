#ifndef _RESPONSE_HPP_
#define _RESPONSE_HPP_

//#include <boost/json.hpp>

//using namespace boost::json;

#include "include/types.hpp"

enum RESPONSE_TYPE
{
    SUCCESS,
    ERROR,
    AUTH_MESSAGE
};

class RESPONSE
{
protected:
    const JsonValue m_JsonResponse;

private:
    RESPONSE_TYPE m_Type;

public:
    explicit RESPONSE( const JsonValue& aJsonResponse );
    bool IsSuccess();
    bool IsError();
    bool IsAuthMessage();
};

#endif // _RESPONSE_HPP_