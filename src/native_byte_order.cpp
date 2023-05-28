#include "native_byte_order.hpp"
#include <cstddef>

void ToNativeByteOrder( size_t aSize, char *aBuffer ) {
    for ( size_t i = 0; i < 4; ++i ) {
        *aBuffer = char(aSize);
        aSize = (aSize >> 8);
        aBuffer++;
    }
}