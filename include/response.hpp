#ifndef _RESPONSE_HPP_
#define _RESPONSE_HPP_

#include <string>

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
private:
    const JsonValue m_JsonResponse;
    std::string     m_FieldType = "";
    std::string     m_FieldDescription = "";
    RESPONSE_TYPE   m_Type;
    void InitFieldData( const std::string& aTypeKey, const std::string& aDescriptionKey );

public:
    explicit RESPONSE( const JsonValue& aJsonResponse );
    RESPONSE_TYPE GetType() const;
    std::string   GetFieldType() const;
    std::string   GetFieldDescription() const;
    bool          IsSuccess() const;
    bool          IsError() const;
    bool          IsAuthMessage() const;
};

#endif // _RESPONSE_HPP_