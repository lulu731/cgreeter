#include "native_byte_order.hpp"
#include <cstddef>

void ToNativeByteOrder( size_t aSize, char *aBuffer ) {
    for ( size_t i = 0; i < 4; ++i ) {
        aBuffer += i;
        *aBuffer = aSize & 0xFF;
        aSize = (aSize >> 8);
    }
}

void FmNativeByteOrder( const char *aBuffer, size_t &aSize ) {
    for (size_t i = 0; i < 4; i++)
    {
        aSize = aSize << 8;
        aSize += aBuffer[3-i] & 0xFF;
    }
}