#ifndef _RESPONSE_HPP_
#define _RESPONSE_HPP_

#include <boost/json.hpp>

using namespace boost::json;

enum RESPONSE_TYPE {
    SUCCESS,
    ERROR,
    AUTH_MESSAGE
};

class RESPONSE
{
protected:
    const value m_JsonResponse;
private:
    RESPONSE_TYPE m_Type;
public:
    RESPONSE( const value &aJsonResponse );
    bool IsSuccess();
    bool IsError();
    bool IsAuthMessage();
};

#endif