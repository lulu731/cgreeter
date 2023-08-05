#define BOOST_TEST_MODULE native byte order

#include "include/native_byte_order.hpp"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( SizeIsOneByte )
{
    const size_t aSize = 46;
    char         aBuffer[4] = { 0, 0, 0, 0 };
    char         aExpected[4] = { aSize, 0, 0, 0 };
    ToNativeByteOrder( aSize, aBuffer );
    BOOST_CHECK_EQUAL_COLLECTIONS( aBuffer, aBuffer + 4, aExpected, aExpected + 4 );
}

BOOST_AUTO_TEST_CASE( SizeIsTwoBytes )
{
    const size_t aSize = 0x2EAB;
    char         aBuffer[4] = { 0, 0, 0, 0 };
    char         aExpected[4] = { static_cast<char>( 0xAB ), static_cast<char>( 0x2E ), 0, 0 };
    ToNativeByteOrder( aSize, aBuffer );
    BOOST_CHECK_EQUAL_COLLECTIONS( aBuffer, aBuffer + 4, aExpected, aExpected + 4 );
}

BOOST_AUTO_TEST_CASE( FmSizeIsOneByte )
{
    size_t aSize = 0;
    char   aBuffer[4] = { 46, 0, 0, 0 };
    FmNativeByteOrder( aBuffer, &aSize );
    BOOST_CHECK_EQUAL( aSize, 46 );
}

BOOST_AUTO_TEST_CASE( FmSizeIsTwoBytes )
{
    size_t aSize = 0;
    char   aBuffer[4] = { static_cast<char>( 0xAB ), static_cast<char>( 0x2E ), 0, 0 };
    FmNativeByteOrder( aBuffer, &aSize );
    BOOST_CHECK_EQUAL( aSize, 0x2EAB );
}