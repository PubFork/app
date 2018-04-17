#pragma once


//typedef uint8_t      byte;
//typedef uint8_t      uchar;
typedef DWORD        dword;
typedef int          int_bool;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using u64 = uint64_t;
using u32 = uint32_t;
using ui16 = uint16_t;
using ui8 = uint8_t;
using f64 = double;
using f32 = float;


#ifdef __cplusplus
template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{
   return (TARGET) src;
}
#endif



//#define WINBOOL int_bool











