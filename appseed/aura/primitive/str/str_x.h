#pragma once

namespace str
{


   CLASS_DECL_AURA bool x_contains(string str, string strFind);
   CLASS_DECL_AURA bool x_find(stringa & stra, string str);
   CLASS_DECL_AURA void x_left_remove(string & str, string strFind);


} // namespace str

CLASS_DECL_AURA extern const char g_ptrailingBytesForUTF8[256];

#define GOOD_AT_BRANCHING 1
#ifdef WINDOWS
#define STRONG_INLINE __forceinline
#else
#define STRONG_INLINE inline
#endif

#if GOOD_AT_BRANCHING

inline int trailingBytesForUTF8_2(char ch)
{
   if (ch >= -64 && ch <= -33)
   {
      return 1;
   }
   else if (ch >= -32 && ch <= -17)
   {
      return 2;
   }
   else if (ch >= -16 && ch <= -9)
   {
      return 3;
   }
   else if (ch >= -8 && ch <= -5)
   {
      return 4;
   }
   else if (ch >= -4 && ch <= -1)
   {
      return 5;
   }
   else
   {
      return -1;
   }
}
// based on the fact that many strings are just ASCII single char
STRONG_INLINE int trailingBytesForUTF8(char ch)
{
   if ((byte)ch <= 192)
   {
      return ch == 0 ? -1 : 0;
   }
   else
   {
      return trailingBytesForUTF8_2(ch);
   }
}
#else
inline int trailingBytesForUTF8(char ch)
{
   return g_ptrailingBytesForUTF8[(byte)ch];
}
#endif


