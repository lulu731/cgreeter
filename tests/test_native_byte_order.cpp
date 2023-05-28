#define BOOST_TEST_MODULE native byte order

#include "native_byte_order.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( SizeIsOneByte)
{
    const size_t aSize = 46;
    char aBuffer[4] = { 0, 0, 0, 0 };
    char aExpected[4] = { aSize, 0, 0, 0 };
    ToNativeByteOrder(aSize, aBuffer);
    BOOST_CHECK_EQUAL_COLLECTIONS( aBuffer, aBuffer + 4,  aExpected, aExpected + 4 );
}

BOOST_AUTO_TEST_CASE( SizeIsTwoBytes)
{
    const size_t aSize = 0x2EAB;
    char aBuffer[4] = { 0, 0, 0, 0 };
    char aExpected[4] = { char(0xAB), char(0x2E), 0, 0 };
    ToNativeByteOrder(aSize, aBuffer);
    BOOST_CHECK_EQUAL_COLLECTIONS( aBuffer, aBuffer + 4,  aExpected, aExpected + 4 );
}