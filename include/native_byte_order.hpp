#ifndef _NATIVE_BYTE_ORDER_HPP_
#define _NATIVE_BYTE_ORDER_HPP_

#include <cstddef>

void ToNativeByteOrder( size_t aSize, char* aBuffer );
void FmNativeByteOrder( const char* aBuffer, size_t& aSize );

#endif